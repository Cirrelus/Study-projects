#include <mpi.h>
#include <iostream>

void Star(int argc, char* argv[]) {
	int ProcNum, ProcRank; // Number of processes and rank of current process
	int NumberOfCycles = atoi(argv[1]); // Number of cycles funcion is required to complete
	int InitialNumber = atoi(argv[2]); // Initial number that first process sends to others
	int TotalSum = 0; // Sum of all processes for mpi_reduce
	//MPI_Status Status; // Status struct for transfering data

	MPI_Init(&argc, &argv); // Start MPI

	// initialize ProcNum and ProcRank
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

	int* AllNumbers = new int[ProcNum+1]; // Array with all numbers
	int IndividualNumber = 0; // Individual number for any process
	double Timer_scatter = 0.0; // Timer for bcast
	double Timer_gather = 0.0; // Timer for reduce

	for (int i = 0; i < NumberOfCycles; i++) {
		MPI_Barrier(MPI_COMM_WORLD); // Wait for other processes
		// Set all numbers on main process
		if (ProcRank == 0)
			if (i == 0)
				for (int i = 0; i < ProcNum + 1; i++)
					AllNumbers[i] = InitialNumber;
			else 
				for (int i = 0; i < ProcNum + 1; i++)
					AllNumbers[i] = TotalSum;
		Timer_scatter -= MPI_Wtime(); // Start point of Bcast timer
		MPI_Scatter(AllNumbers, 1, MPI_INT, &IndividualNumber, 1, MPI_INT, 0, MPI_COMM_WORLD); // Send the current number to all processes
		IndividualNumber += ProcRank; // Set individual number
		MPI_Barrier(MPI_COMM_WORLD); // Wait for other processes
		Timer_scatter += MPI_Wtime(); // End point of bcast timer
		Timer_gather -= MPI_Wtime(); // Start point of reduce timer
		MPI_Gather(&IndividualNumber, 1, MPI_INT, AllNumbers, 1, MPI_INT, 0, MPI_COMM_WORLD); // Summarie individual numbers
		Timer_gather += MPI_Wtime(); // End point of reduce timer
		// Calculate current sum
		if (ProcRank == 0)
			for (int j = 0; j < ProcNum; j++)
				TotalSum += AllNumbers[j];
	}

	// Showcase final result
	if (ProcRank == 0) {
		printf("Sum = %d\n", TotalSum); fflush(0);
		printf("Scatter time = %f\n", Timer_scatter); fflush(0);
		printf("Gather time = %f\n", Timer_gather); fflush(0);
	}

	delete[] AllNumbers;
	MPI_Finalize(); // Stop MPI	
}

int main(int argc, char* argv[]) {
	// Console command: mpiexec -np (number of processes) MPI_Star_Bcast.exe (number of cycles) (initial number)
	// For example: mpiexec -np 5 MPI_Star_Scatter.exe 3 0
	Star(argc, argv);
	return 0;
}