#!/usr/bin/env perl
$get = (sub{return scalar @ARGV == 0 ? shift : shift @ARGV});
my $max = $get->(1e9);
print int(rand() * $max)." " for (1..((1)->$get));
print "\n"
