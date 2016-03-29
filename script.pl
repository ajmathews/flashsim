#!/usr/bin/perl
#@files = ("Financial1", "Financial2", "WebSearch1", "WebSearch2", "WebSearch3");
@confFiles = ('ssd.conf', 'ssd2.conf', 'ssd3.conf', 'ssd4.conf');
$ext = ".spc";
$outputFile = "output.txt";

foreach $file (@confFiles) {
	#$fileNew = $file.$ext;
	system("date");
	system("mv $file ssd.conf");
	
	system("echo '\n------------Config file :  $file \n'");
	system("./dftl Financial2.spc");

	system("rm ssd.conf");
  
}

#
#foreach $file (@files) {
#	$fileNew = $file.".100".$ext;
    #system("head -100 $file$ext > $fileNew");
#}
