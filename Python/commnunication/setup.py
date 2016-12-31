from distutils.core import setup, Extension

module1 = Extension( "exmod" ,
	include_dirs = ["/usr/local/include"],
	libraries = ["wiringPi"],
	sources = ["speedUp.c"] )

setup( name = "exmod",
	description = "sample",
	ext_modules = [module1] )