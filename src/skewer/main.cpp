
/**********************************************************************
 * Skewer - a fast and accurate adapter trimming tool
 *          using the bit-masked k-difference matching algorithm
 * Copyright (c) 2013-2016 by Hongshan Jiang
 * hongshan.jiang@gmail.com
 *
 * If you use this program, please cite the paper:
 * Jiang, H., Lei, R., Ding, S.W. and Zhu, S. (2014) Skewer: a fast and
 * accurate adapter trimmer for next-generation sequencing paired-end reads.
 * BMC Bioinformatics, 15, 182.
 * http://www.biomedcentral.com/1471-2105/15/182
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "main.hpp"
int main(int argc, const char * argv[])
{
    skewer::main( argc, argv );
}
