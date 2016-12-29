#!/usr/bin/env perl
$get = (sub{return scalar @ARGV == 0 ? shift : shift @ARGV});
print int(rand() * $get->(1e9))." " for (1..($get->(1)));
print "\n"
