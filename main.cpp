// =============================================================================
// use DB select a seed and clustering                   
// 
// =============================================================================

#include "mcl.h"
#include<ctime>
#include <fstream>
#include <iostream>
#include <string>
//#ifdef min
#undef min
#undef max
//#endif
//#define min(a,b) ( ((a) < (b)) ? (a) : (b) )
//#define max(a,b) ( ((b) > (a)) ? (b) : (a) )
#include <sstream>
using namespace std;
Options options;
SequenceDB seq_db;

////////////////////////////////////  MAIN /////////////////////////////////////
int main(int argc, char *argv[])
{
	string db_in;
	string db_out;
	clock_t start,finish;
	start=clock();
	double totaltime;
	
	if (argc < 7){
		print_usage(argv[0]);
		return 0;
	}
	
	if (options.SetOptions( argc, argv ) == 0) print_usage(argv[0]);
	//int argc=7;
	//char *argv[ ]={"./dbClust","-i" ,"E:\\C++\\data\\case2_10000.txt", "-o" ,"case2_db_90" ,"-c", "0.90"};
	options.SetOptions( argc, argv );
	options.Validate();

	db_in = options.input;   //options的类成员
	db_out = options.output; //options的类成员

	InitNAA( MAX_UAA );
	options.NAAN = NAAN_array[options.NAA];
	seq_db.NAAN = NAAN_array[options.NAA];

	//printf( "%i  %i  %i\n", sizeof(NVector<IndexCount>), seq_db.NAAN, sizeof(NVector<IndexCount>) * seq_db.NAAN );

	seq_db.Read( db_in.c_str(), options );
	//cout << "\nTotal seq: " << seq_db.sequences.size() << endl;

	//printf("\n第%d个seq是",pre[vv]+1);
	//printf("第%d个seq是%s\n",0,seq_db.sequences[0]->data2);
	
	int max_length=seq_db.SortDivide( options );
	//printf("第%d个seq是%s\n",0,seq_db.sequences[0]->data2);
	
	//cout << finish-start   << "/" << CLOCKS_PER_SEC  << " (s) "<< endl;
	//seq_db.DoClustering( options );//three seeds

	seq_db.DoClustering1( options );// 
	//printf("第%d个seq是%s\n",0,seq_db.sequences[0]->data2);
	
	//printf( "\nwriting new database\n" );

	//seq_db.WriteClusters( db_in.c_str(), db_out.c_str(), options );
	
	//printf("\n第%d个seq是%s",0,seq_db.sequences[0]->data);
	Vector< Vector<int> > pre=seq_db.WriteExtra1D1( options );
	seq_db.Read( db_in.c_str(), options );
	// seq_db.correct_precluster(options,pre);
	//////////////////////////////////////  自己写的，每类是一行
	printf("\nComputing DB graph...\n" );

	seq_db.correct_precluster(options,pre,max_length);

	seq_db.WriteCorrectedSeq( options );
	//seq_db.Read( db_in.c_str(), options );
	int iii;
	string qq1=options.output;
	char qq2[35];
	char qq3[35];
	for ( iii=0;iii<qq1.length();iii++){
		qq2[iii]=qq1[iii];
		qq3[iii]=qq1[iii];
	}
	qq3[iii]='\0';
	string all_seqs_after_db = strcat(qq3 , ".after_db");
   // seq_db.correct_precluster(options,pre);
	//////////////////////////////////////  自己写的，每类是一行
	seq_db.Read( all_seqs_after_db.c_str(), options );
	max_length=seq_db.SortDivide( options );
	//printf("第%d个seq是%s\n",0,seq_db.sequences[0]->data2);

	//cout << finish-start   << "/" << CLOCKS_PER_SEC  << " (s) "<< endl;
	//seq_db.DoClustering( options );//three seeds

	seq_db.DoClustering1( options );// one seed
	//printf("第%d个seq是%s\n",0,seq_db.sequences[0]->data2);

	printf( "\nwriting new database\n" );

	//seq_db.WriteClusters( db_in.c_str(), db_out.c_str(), options );

	//printf("\n第%d个seq是%s",0,seq_db.sequences[0]->data);
	seq_db.WriteExtra1D2( options );
	cout << "\nprogram completed!------->"<<seq_db.rep_seqs.size()<<" clusters" << endl;
	time_t tm = time(NULL);
	printf( "Finished at: %s", ctime(&tm) );
	//printf( "\nTotal CPU time %.2f s\n", totaltime );
	//system("pause");
	return 0;
} // END int main
