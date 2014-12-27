AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = dbt
dbt_SOURCES = src/main.cc
dbt_LDADD = $(LIBOJBS) -lconfig++ -lcairo
dbt_LDFLAGS = -I/usr/include/cairo
AM_CPPFLAGS = -I/usr/include/cairo -std=c++0x
AM_CFLAGS = 
