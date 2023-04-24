#include <mpi.h>
#include <iostream>
#include <string>

void Circle(int argc, char* argv[]) {
	int ProcNum, ProcRank; // Number of processes and rank of current process
	int NumberOfCircles = atoi(argv[1]); // Number of circles funcion is required to complete
	char* Message = argv[2]; // Initial message that function transfers
	int length = sizeof(Message) / sizeof(char) + 1; // Length of message
	MPI_Status Status; // Status struct for transfering data

	MPI_Init(&argc, &argv); // Start MPI
	
	// initialize ProcNum and ProcRank
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

	char* Last_Message = new char[length]; // Individual buffer for message for any process

	for (int i = 0; i < NumberOfCircles; i++) {
		if (ProcRank == 0) // First process starts sending message
		{	
			// At first circle send initial message
			if (i == 0) {
				printf("%d->%d: Message - %s, Circle - %d\n", ProcRank, ProcRank + 1, Message, i); fflush(0);
				MPI_Ssend(Message, length, MPI_CHAR, ProcRank + 1, 0, MPI_COMM_WORLD);
			}
			// After first circle send received message
			else {
				printf("%d->%d: Message - %s, Circle - %d\n", ProcRank, ProcRank + 1, Last_Message, i); fflush(0);
				MPI_Ssend(Last_Message, length, MPI_CHAR, ProcRank + 1, 0, MPI_COMM_WORLD);
			}
			// Receive the message from last process
			MPI_Recv(Last_Message, length, MPI_CHAR, ProcNum - 1, 0, MPI_COMM_WORLD, &Status);
		}
		// Last process receives the message from previous process and then sends it to the first
		else if (ProcRank == ProcNum - 1)
		{
			MPI_Recv(Last_Message, length, MPI_CHAR, ProcRank - 1, 0, MPI_COMM_WORLD, &Status);
			printf("%d->%d: Message - %s, Circle - %d\n", ProcRank, 0, Last_Message, i); fflush(0);
			MPI_Ssend(Last_Message, length, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
		}
		// Any other process receives the from previous process and then sends it to the next
		else
		{
			MPI_Recv(Last_Message, length, MPI_CHAR, ProcRank - 1, 0, MPI_COMM_WORLD, &Status);
			printf("%d->%d: Message - %s, Circle - %d\n", ProcRank, ProcRank + 1, Last_Message, i); fflush(0);
			MPI_Ssend(Last_Message, length, MPI_CHAR, ProcRank + 1, 0, MPI_COMM_WORLD);
		}
	}

	// Showcase final result
	if (ProcRank == 0)
		if(std::strcmp(Message, Last_Message) == 0) {
			printf("\"%s\" = \"%\s\"\n", Message, Last_Message); 
			printf("Completed Successfully\n");
		}
		else{
			printf("\"%s\" != \"%\s\"\n", Message, Last_Message);
			printf("Not completed Successfully\n");
		}

	delete[] Last_Message;
	
	MPI_Finalize(); // Stop MPI	
}

int main(int argc, char *argv[]) {
	// Console command: mpiexec -np (number of processes) MPI_Circle.exe (number of circles) (text message)
	// For example: mpiexec -np 5 MPI_Circle 4 Test
	Circle(argc, argv);
	return 0;
}