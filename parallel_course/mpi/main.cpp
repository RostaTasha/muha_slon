#include <iostream>
#include <fstream>
#include "mpi.h"
#include <vector>
#include <cstring>

//#define DEBUG



int * merge(int * A, int * B, int asize, int bsize) {
	int csize = asize+ bsize;

	int * C = new int[csize];

	int ai = 0;
	int bi = 0;
	int ci = 0;

	while ((ai < asize) && (bi < bsize)) {
		if (A[ai] <= B[bi]) {
			C[ci] = A[ai];
			ci++; ai++;
		} else {
			C[ci] = B[bi];
			ci++; bi++;
		}
	}

	if (ai >= asize)
		for (int i = ci; i < csize; i++, bi++)
			C[i] = B[bi];
	else if (bi >= bsize)
		for (int i = ci; i < csize; i++, ai++)
			C[i] = A[ai];

	for (int i = 0; i < asize; i++)
		A[i] = C[i];
	for (int i = 0; i < bsize; i++)
		B[i] = C[asize+i];
				
	return C;
}


void sort_all(int * array, int ar_size, int n, int chunk){
	if (n==1) return;
	
	int size = chunk;
	int size_last = ar_size-chunk*(n-1);
	for (int i =0; i<n/2;i++){
		int size_1 = size;
		int size_2 = ((2*i+1)==(n-1)) ? size_last : size;
		int * temp=merge(array+2*i*size,array+(2*i+1)*size,size_1,size_2);
		std::memcpy(array+size*2*i,temp,size*2);
		delete [] temp;
	}
	

		
	sort_all(array, ar_size, n/2+n%2,2*chunk);

}

void  merge_helper(int *input, int left, int right)
{
	/* base case: one element */
	if(right == left )
    {
        return;
    }
    else
    {
        int length = right - left+1;
        int midpoint_distance = length/2;
        /* l and r are to the positions in the left and right subarrays */
        int l = left, r = left + midpoint_distance;

        /* sort each subarray */
        merge_helper(input, l, r-1);
        merge_helper(input, r, right);
		
		int * C = merge(input+l, input+r, r-l,right-r+1);
		std::memcpy(input+left,C,length);
		delete [] C;
		
		return;
}

}
		
int main(int argc, char** argv){
std::vector<int> array;
array.reserve(10);
#ifdef DEBUG	
	for (int i =0; i< 10; i++)
		array.push_back(10-i-1);
#else
	std::ifstream infile("/mnt/Backup/users/tasha/dataset.txt");
	int temp;
	while (infile>>temp) array.push_back(temp);
#endif

	MPI::Init(argc, argv);
	int nprocs= MPI::COMM_WORLD.Get_size();
	int myid=MPI::COMM_WORLD.Get_rank();
	int size = array.size()/nprocs;
	int last_size=array.size()-nprocs*size+size; //in case there array.size()%nprocs!=0 last_size!=size

	int * subarray  = new int[last_size];	
    int * scounts 	= new int [nprocs];
    int * offset 	= new int [nprocs];
	
	
        for (int i=0; i<nprocs; ++i) {
			offset[i] = i*size;
            scounts[i] = (i!=nprocs-1) ? size : last_size;
        }
		
	/*void MPI::Comm::Scatterv(const void* sendbuf, const int sendcounts[],
    const int displs[], const MPI::Datatype& sendtype,
    void* recvbuf, int recvcount, const MPI::Datatype&
    recvtype, int root) const	*/
	// scatter from 0 to all
	

	MPI::COMM_WORLD.Scatterv(&(array[0]),scounts,offset,MPI_INT,subarray,last_size,MPI_INT,0);

/*

	MPI::Datatype style(MPI_INT);
	style.Create_contiguous(myid==(nprocs-1) ? last_size : size);
	
	MPI::COMM_WORLD.Gatherv(subarray,1,style,sorted,scounts,offset,MPI_INT,0);

*/
	if (myid==(nprocs-1))
		merge_helper(subarray, 0, last_size-1);
	else
		merge_helper(subarray, 0, size-1);
		

	//MPI::Finalize();
	//return 0;
	int * sorted;
	if (myid==0){
		sorted = new int[array.size()];
	}
	/*void MPI::Comm::Gatherv(const void* sendbuf, int sendcount,
    const MPI::Datatype& sendtype, void* recvbuf,
    const int recvcounts[], const int displs[],
    const MPI::Datatype& recvtype, int root) const = 0*/
	// gather by 0 from all

	
	MPI::COMM_WORLD.Gatherv(subarray,myid==(nprocs-1) ? last_size : size,MPI_INT,sorted,scounts,offset,MPI_INT,0);
	if (myid==0){
		sort_all(sorted,array.size(),nprocs,size);
		//merge_helper(sorted, 0, array.size()-1);
		
#ifdef DEBUG		
		for (int i=0; i<array.size();i++) 
			std::cout<<sorted[i]<<std::endl;
		delete [] sorted;
#else
	std::ofstream outfile("/mnt/Backup/users/tasha/dataset_o.txt");
	for (int i=0; i<array.size();i++) 
		outfile<<sorted[i]<<" ";
#endif
	}
	
	delete []	scounts;
    delete [] 	offset;
	delete []  	subarray;
	MPI::Finalize();
	return 0;
}


