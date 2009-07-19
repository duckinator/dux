my $value = `uname -m`;
chomp($value);
print "#define __DUX_BUILT_ARCH__ \"" . $value . "\"\n";

$value = `uname -o`;
chomp($value);
print "#define __DUX_BUILT_OS__ \"" . $value . "\"\n";

$value = `uname -r`;
chomp($value);
print "#define __DUX_BUILT_VERSION__ \"" . $value . "\"\n";

$value = `uname -n`;
chomp($value);
print "#define __DUX_BUILT_NAME__ \"" . $value . "\"\n";

$value = `date`;
chomp($value);
print "#define __DUX_BUILT_DATE__ \"" . $value . "\"\n";
