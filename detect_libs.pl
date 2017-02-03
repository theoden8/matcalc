#!/usr/bin/env perl

use strict;
use warnings;

my $sought = {
  '#include <math.h>' => '-lm',
  '#include <cmath>' => '-lm',
  '#include <gmp.h>' => '-lgmp',
  '#include <gmpxx.h>' => '-lgmpxx -lgmp',
  '#include <mpfr.h>' => '-lmpfr',
  '#include <pthread.h>' => '-pthread'
};

my %inclusions;
my %found;

my @includes = ();
while(<>) {
  while(my($k, $v) = each %$sought) {
    $found{$k} = $v if(/$k/);
  }
  my $l = undef;
  if(/#include ".*\.h"/) {
    my $l = $_;
    $l =~ s/(#include "|")//g;
  }
  if($l) {
    if(not exists $inclusions{$l}) {
      push @ARGV, $l;
    }
    $inclusions{$l} = $l;
  }
}

print (join " ", values %found);
