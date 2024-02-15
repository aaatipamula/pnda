#/usr/bin/env perl

# Enforce stricter code rules and warn of deviations
use strict;
use warnings;

# Import tab expansion functions set tabstop to 2 characters
use Text::Tabs;
$tabstop = 2;

sub defineType {
  my ($fileHandle, $baseName, $className, $fields) = @_;
  my @fieldsA = split(", ", $fields);

  print $fileHandle "\n\nclass $className : public $baseName {\n";
  print $fileHandle expand("\tpublic:\n");
  print $fileHandle expand("\t\t$className($fields) {\n");
  foreach my $field (@fieldsA) {
    my ($type, $name) = split(" ", $field);
    print $fileHandle expand("\t\t\t_$name = $name;\n");
  }
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
  print $fileHandle "#include <token.h>\n\n";
  print $fileHandle "class $baseName {\n";
  print $fileHandle expand("\tprotected:\n");
  print $fileHandle expand("\t\tconst $baseName *_left;\n");
  print $fileHandle expand("\t\tconst $baseName *_right;\n");
  print $fileHandle expand("\t\tconst $baseName *_expression;\n");
  print $fileHandle expand("\t\tconst Token _oper;\n");
  print $fileHandle expand("\t\tconst std::any _value;\n");
  print $fileHandle "};";

  foreach my $exprType (@exprTypes) {
    my ($className, $fields) = split(" : ", $exprType);
    defineType($fileHandle, $baseName, $className, $fields);
  }

  print $fileHandle "#endif";
}

my $dir = "./";

my $name = "Expr";

my @types = (
  "Binary : $name left, Token oper, $name right",
  "Grouping : $name expression",
  "Literal : std::any value",
  "Urnary : Token oper, $name right"
);

defineAst($dir, $name, @types);
