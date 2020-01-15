print "Hello, Perl\n";

open(IN, "LICENSE");
while (<IN>) { print $_; }
close(IN);
