# RefGen
User Manual for RefGen version 1.0

CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Installation
 * Usage
 * Troubleshooting
 * Maintainers

INTRODUCTION
------------

Given a set of experiments this algorithm takes as input a list of genomic intervals, and it returns a reference defined by the genomic positions which are spanned by more than τ intervals. RefGen first exploits the lists of genomic intervals to generate a genomic coverage (i.e. the overlapping value among intervals), then the genomic position characterized by a coverage value greater than or equal to a selected threshold τ are selected as reference.

The use of the τ threshold makes the overlap of multiple experiments independent of the length and the number of genomic regions belonging to the input datasets. Since the τ value reflects the number of experiments in which the genomic regions have to be identify, the selection of a specific τ value is related to the level of the severity chosen for the analysis.

For details of this analysis see:

Please cite this paper when using this code.

REQUIREMENTS
------------

 * C++
 * Perl (optional, for identification of multiple genomic intervals)

INSTALLATION
------------
 
 * You may use RefGen algorithm by directly run the 64-bit binary file (no compilation is needed), or you may build it from the source. For build the program from source type "make" in the installation folder.

USAGE
-------------
 
 * For RefGen usage on a specific genomic interval:

	RefGen <input_file> <output_file> <lower_bound> <upper_bound> <threshold> <Chromosome>

		- input_file = Name of the input file;
		- output_file = Name of the output file;
		- lower_bound = Starting position of the genomic region of interest (in 0-based system);
		- upper_bound = End position of the genomic region of interest (in 0-based system);
		- threshold = τ threshold representing the minimum number of genomic intervals that have to be overlapped to define an output interval;
		- Chromosome = Chromosome identifier.

 * For an automatic application of RefGen on multiple genomic intervals:

	perl Run.pl <input_file> <chrs> <threshold>

		- input_file = The folder which collects the input datasets;
		- chrs = Tab-separated file reporting the name and the lenght of the chromosome analysed. Chromosome length for human genome hg18, hg19 and hg38 are
				 provided in the Chromosome_sizes folder;
		- threshold = τ threshold representing the minimum number of genomic regions reporting overlapped within the genomic region of interest.
		
 * Example of single chromosome (chr1) analysis to identify intervals observed in all the 3 experiment replicates:

		cat ./Input_example/*.bed > ./Input_example/Input_merged.bed
		
		./RefGen ./Input_example/Input_merged.bed ./Input_example/Overlapped_regions_chr1.bed 0 249250621 3 chr1

 * Example of multiple chromosome analysis:	

		cat ./Input_example/*.bed > ./Input_example/Input_merged.bed

		perl Run.pl ./Input_example/Input_merged.bed ./Chromosome_sizes/hg19.chrom.sizes.txt 3

MAINTAINERS
-----------

 * Beccuti Marco (University of Turin) - http://www.di.unito.it/~beccuti/
 * Ferrero Giulio (University of Turin) - http://www.di.unito.it/~ferrero/

/***************************************************************************
 *   Copyright (C) 2016 by Marco Beccuti and Giulio Ferrero                *
 *   beccuti@di.unito.it    											   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
Contact GitHub API Training Shop Blog About
© 2017 GitHub, Inc. Terms Privacy Security Status Help
