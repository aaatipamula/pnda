#!/usr/bin/perl

# Enforce stricter code rules and warn of deviations
use strict;
use warnings;

# Import tab expansion functions set tabstop to 2 characters
use Text::Tabs;
$tabstop = 2;

# Write out a class that extends the base class
sub defineType {
  # Grab and store subroutine inputs
  my ($fileHandle, $baseName, $className, $fields) = @_;
  $fields =~ s/$baseName/std::unique_ptr<$baseName>/g;
  my @fieldsA = split(", ", $fields);

  # Class inherits from base class
  print $fileHandle "\n\nclass $className : public $baseName {\n";
  # Define any new class attributes that don't exist in the base class
  foreach my $field (@fieldsA) {
    print $fileHandle expand("\t$field;\n");
  }
  # Public methods/attributes
  print $fileHandle expand("\tpublic:\n");
  # Write the constructor
  print $fileHandle expand("\t\t$className($fields)\n\t\t\t: ");
  # Instantiate each of the class attributes
  for(my $i = 0; $i < scalar(@fieldsA); $i++) {
    my ($type, $name) = split(" ", $fieldsA[$i]);
    my $val;
    # If value is a unique pointer move it into the class pointer
    if ($type eq "std::unique_ptr<$baseName>") {
      $val = "$name(std::move($name)), ";
    # Set values of class attributes
    } else {
      $val = "$name($name), ";
    }
    # If we are at our last class attribute remove the comma-space seperator
    if ($i == $#fieldsA) {
      print $fileHandle substr($val, 0, -2);
    } else {
      print $fileHandle $val;
    }
  }
  # close off the class constructor and declaration
  print $fileHandle " {}\n";
  print $fileHandle "};";
}

sub defineAst {
  # Store output directory
  # Store the the class name we want
  # Store the types
  my ($outputDir, $baseName, @exprTypes) = @_;

  my $fileHandle = undef; # Create a scalar to save filehandler in
  my $filePath = $outputDir . "/" . $baseName . ".h"; # Compose /path/to/file

  # Save filehandler with write permissions in utf-8 encoding
  open($fileHandle, "> :encoding(UTF-8)", $filePath) 
    or die "$0: Cannot open $filePath for writing: $!";

  my $upperBaseName = uc $baseName;

  # Setup header file and include required libraries
  print $fileHandle "#ifndef $upperBaseName\_H\n";
  print $fileHandle "#define $upperBaseName\_H\n\n";
  print $fileHandle "#include <any>\n";
  print $fileHandle "#include <memory>\n";
  print $fileHandle "#include <utility>\n";
  print $fileHandle "#include \"token.h\"\n\n";

  # Write out the abstract class
  print $fileHandle "class $baseName {\n";
  print $fileHandle expand("\tpublic:\n");
  print $fileHandle expand("\t\tvirtual ~$baseName() = default;\n");
  print $fileHandle "};";

  # For each class name define it
  foreach my $exprType (@exprTypes) {
    my ($className, $fields) = split(" : ", $exprType);
    defineType($fileHandle, $baseName, $className, $fields);
  }

  # Close the header file
  print $fileHandle "\n\n#endif\n";
}

################
# MAIN PROGRAM #
################

# Grab the directory from command line args and exit if we have not found one
my $dir = shift @ARGV;
if (not defined $dir) {
  die "Missing ouput directory argument"
}

# Define the base class name and the subclasses we want to use
my $name = "Expr";
my @types = (
  "Binary : $name left, Token oper, $name right",
  "Grouping : $name expression",
  "Literal : std::any value",
  "Urnary : Token oper, $name right"
);

# Define our AST file
defineAst($dir, $name, @types);

