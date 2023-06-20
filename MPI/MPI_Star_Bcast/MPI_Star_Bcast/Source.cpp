#include <mpi.h>
#include <iostream>

void Star(int argc, char* argv[]) {
	int ProcNum, ProcRank; // Number of processes and rank of current process
	int NumberOfCycles = atoi(argv[1]); // Number of cycles funcion is required to complete
	int InitialNumber = atoi(argv[2]); // Initial number that first process sends to others
	int TotalSum = 0; // Sum of all processes for mpi_reduce
	MPI_Status Status; // Status struct for transfering data

	MPI_Init(&argc, &argv); // Start MPI

	// initialize ProcNum and ProcRank
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

	int IndividualNumber = 0; // Individual number for any process
	double Timer_bcast = 0.0; // Timer for bcast
	double Timer_reduce = 0.0; // Timer for reduce

	for (int i = 0; i < NumberOfCycles; i++) {
		MPI_Barrier(MPI_COMM_WORLD); // Wait for other processes
		// Set Individual number
		if (ProcRank == 0)
			if (i == 0) IndividualNumber = InitialNumber;
			else IndividualNumber = TotalSum;
		Timer_bcast -= MPI_Wtime(); // Start point of Bcast timer
		MPI_Bcast(&IndividualNumber, 1, MPI_INT, 0, MPI_COMM_WORLD); // Send the current number to all processes
		IndividualNumber += ProcRank; // Set individual number
		MPI_Barrier(MPI_COMM_WORLD); // Wait for other processes
		Timer_bcast += MPI_Wtime(); // End point of bcast timer
		Timer_reduce -= MPI_Wtime(); // Start point of reduce timer
		MPI_Reduce(&IndividualNumber, &TotalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); // Summarie individual numbers
		Timer_reduce += MPI_Wtime(); // End point of reduce timer
	}

	// Showcase final result
	if (ProcRank == 0) {
		printf("Sum = %d\n", TotalSum); fflush(0);
		printf("Bcast time = %f\n", Timer_bcast); fflush(0);
		printf("Reduce time = %f\n", Timer_reduce); fflush(0);
	}

	MPI_Finalize(); // Stop MPI	
}

int main(int argc, char* argv[]) {
	// Console command: mpiexec -np (number of processes) MPI_Star_Bcast.exe (number of cycles) (initial number)
	// For example: mpiexec -np 5 MPI_Star_Bcast.exe 3 0
	Star(argc, argv);
	return 0;
}