#/usr/bin/env perl

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
  my @fieldsA = split(", ", $fields);

  # Class inherits from base class
  print $fileHandle "\n\nclass $className : public $baseName {\n";
  # Define any new class attributes that don't exist in the base class
  foreach my $field (@fieldsA) {
    my ($type, $name) = split(" ", $field);
    if (!(grep(/^$name$/, ("left", "right", "oper")))) {
      print $fileHandle expand("\t$type _$name;\n");
    }
  }
  # Public methods/attributes
  print $fileHandle expand("\tpublic:\n");
  # Write the constructor
  print $fileHandle expand("\t\t$className($fields) {\n");
  # Instantiate each of the class attributes
  foreach my $field (@fieldsA) {
    my ($type, $name) = split(" ", $field);
    print $fileHandle expand("\t\t\t_$name = $name;\n");
  }
  # close off the class declaration
  print $fileHandle expand("\t\t}\n");
  print $fileHandle expand("};\n");
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

  # Write out the abstract class
  print $fileHandle "#ifndef $upperBaseName\_H\n";
  print $fileHandle "#define $upperBaseName\_H\n\n";
  print $fileHandle "#include <any>\n";
  print $fileHandle "#include \"token.h\"\n\n";
  print $fileHandle "class $baseName {\n";
  print $fileHandle expand("\tprotected:\n");
  print $fileHandle expand("\t\t$baseName* _left;\n");
  print $fileHandle expand("\t\t$baseName* _right;\n");
  print $fileHandle expand("\t\tToken _oper;\n");
  print $fileHandle "};";

  foreach my $exprType (@exprTypes) {
    my ($className, $fields) = split(" : ", $exprType);
    defineType($fileHandle, $baseName, $className, $fields);
  }

  print $fileHandle "\n#endif";
}

my $dir = shift @ARGV;

if (not defined $dir) {
  die "Missing ouput directory argument"
}

my $name = "Expr";
my @types = (
  "Binary : $name* left, Token oper, $name* right",
  "Grouping : $name* expression",
  "Literal : std::any value",
  "Urnary : Token oper, $name* right"
);

defineAst($dir, $name, @types);
