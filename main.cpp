#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <string>
using namespace std;

const int MAX_DATA=100;
void listProducts(float maxPrice);
string get_query(char* szFee);
string a_choice(char* szFee);
string al_choice(char* szFee);
string s_choice(char* szFee);
string g_choice(char* szFee);
string GetQuery_1(char* szPrice);
string GetQuery_2(char* szFee);
string GetQuery_3(char* szFee);
string GetQuery_4(char* szFee);
string GetQuery_5(char* szFee, string a_n);
string GetQuery_6(char* szFee, string a_n);
string GetQuery_7(char* szFee, string al_n);
string GetQuery_8(char* szFee, string al_n);
string GetQuery_9(char* szFee, string s_n);
string GetQuery_10(char* szFee, string s_n);
string GetQuery_11(char* szFee, string g_n);
string GetQuery_12(char* szFee, string g_n);
string GetQuery_13(char* szFee, string a_n);
string GetQuery_14(char* szFee, string a_n);
string GetQuery_15(char* szFee, string s_n);
string GetQuery_16(char* szFee, string g_n);


int main() {

	int again = 1;
	
	while (again == 1)
	{
		listProducts(20.5);
		cout << endl;
		cout << "Run again? (1 for yes, 0 for no)" << endl;
		cin >> again;
	}


	system("pause");

	return 0;
}

void listProducts(float maxPrice) {
	RETCODE rc;
	HENV henv;
	HDBC hdbc;
	HSTMT hstmt;
	char szData[MAX_DATA];
	string stSQL;
	SQLLEN cbData;
	char szPrice[10];
	
	_gcvt_s(szPrice, 10, maxPrice, 6);

	SQLAllocEnv(&henv);
	SQLAllocConnect(henv, &hdbc);

	SQLCHAR szConnectOut[1024];
	SQLSMALLINT cchConnect;

	
	string stConnect = "DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=C:\\Users\\abagnall-smith20\\Desktop\\MusicDatabasev1.accdb;UID=Admin;PWD=;";



	// CALLS QUERY FUNCTIONS
	stSQL = get_query(szPrice);

	rc = SQLDriverConnect(hdbc, NULL, (SQLCHAR *) stConnect.c_str(), stConnect.length(), szConnectOut, 1024, &cchConnect, SQL_DRIVER_NOPROMPT);
	if (!(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO))
	{
		SQLTCHAR state[255], error[255];
		SQLINTEGER code;
		SQLSMALLINT cb;
		SQLError(henv, hdbc, NULL, state, &code, error, 255, &cb);
		cout << error << endl;
		exit(0);
	}
	SQLAllocStmt(hdbc, &hstmt);
	cout << stSQL << endl;
	rc = SQLExecDirect(hstmt, (SQLCHAR*) stSQL.c_str(), SQL_NTS);
	if (!(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO))
	{
		SQLTCHAR state[255], error[255];
		SQLINTEGER code;
		SQLSMALLINT cb;
		SQLError(henv, hdbc, hstmt, state, &code, error, 255, &cb);
		cout << error << endl;
		exit(0);
	}


	//DISPLAY THE RESULTS OF THE QUERY

	int i = 0;

	
		while (rc == SQL_SUCCESS && i < 100) {
			rc = SQLFetch(hstmt);
			if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << "   " << szData << "   " ;
			if (SQLGetData(hstmt, 2, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << szData<<"   ";
			if (SQLGetData(hstmt, 3, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << szData<<"   ";
			if (SQLGetData(hstmt, 4, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << szData<<"   ";
			if (SQLGetData(hstmt, 5, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << szData<<"   ";

			cout << endl;
			
			i++;
		}
		


	SQLFreeStmt(hstmt, SQL_DROP);
	SQLDisconnect(hdbc);
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);
}



// Get the query using user input.
string get_query(char* szFee)
{
	string u_resp = "";
	string to_send = "";
	

	cout << "Would you like information on artists, albums, songs, or genres? ";
	cin >> u_resp;

	// PUT THESE IN ANOTHER FUNCTION BASED ON THE TYPE
	if (u_resp == "artists" || u_resp == "Artists")
	{
		to_send = a_choice(szFee);		
	}
	else if (u_resp == "albums" || u_resp == "Albums")
	{
		to_send = al_choice(szFee);
	}
	else if (u_resp == "songs" || u_resp == "Songs")
	{
		to_send = s_choice(szFee);
	}
	else if (u_resp == "genres" || u_resp == "Genres")
	{
		to_send = g_choice(szFee);
	}


	return to_send;
}


// *****************************************USER CHOICES***************************************************

//ARTISTS    (DONE)
string a_choice(char* szFee)
{
	int q_num = 0;
	string sender;

	string a_name = "";
	cout << "Enter the number corresponding with the information that you would like from the provided list: " << endl;
	cout << "1) All artist infromation" << endl;
	cout << "2) Number of songs by a given artist" << endl;
	cout << "3) Number of albums by a given artist" << endl;
	cout << "4) List all songs by a given artist" << endl;
	cout << "5) List all albums by a given artist" << endl;
	cin >> q_num;

	cin.clear();
	cin.ignore(1000000, '\n');           // Clear cin so I can use getline.

	if (q_num == 2)
	{
		cout << "Name of the artist: ";
		getline(cin, a_name);
		sender = GetQuery_6(szFee, a_name);
	}
	else if (q_num == 3)
	{
		cout << "Name of the artist: ";
		getline(cin, a_name);
		sender = GetQuery_5(szFee, a_name);
	}
	else if (q_num == 4)
	{
		cout << "Name of the artist: ";
		getline(cin, a_name);
		sender = GetQuery_13(szFee, a_name);
	}
	else if (q_num == 5)
	{
		cout << "Name of the artist: ";
		getline(cin, a_name);
		sender = GetQuery_14(szFee, a_name);
	}
	else
		sender = GetQuery_1(szFee);	

	return sender;


}


//ALBUMS        (DONE)
string al_choice(char* szFee)
{
	int q_num = 0;
	string sender;

	string al_name = "";
	cout << "Enter the number corresponding with the information that you would like from the provided list: " << endl;
	cout << "1) All album infromation" << endl;
	cout << "2) Number of songs on a given album" << endl;
	cout << "3) All song titles on a given album" << endl;
	cin >> q_num;

	cin.clear();
	cin.ignore(1000000, '\n');           // Clear cin so I can use getline.

	if (q_num == 2)
	{
		cout << "Name of the album: ";
		getline(cin, al_name);
		sender = GetQuery_7(szFee, al_name);
	}
	else if (q_num == 3)
	{
		cout << "Name of the album: ";
		getline(cin, al_name);
		sender = GetQuery_8(szFee, al_name);
	}
	else
		sender = GetQuery_2(szFee);

	return sender;
}


//SONGS            (DONE)
string s_choice(char* szFee)
{
	int q_num = 0;
	string sender;

	string s_name = "";
	cout << "Enter the number corresponding with the information that you would like from the provided list: " << endl;
	cout << "1) All song information" << endl;
	cout << "2) Song title and artist" << endl;
	cout << "3) Song title and album" << endl;
	cout << "4) Song title and genre" << endl;
	cin >> q_num;

	cin.clear();
	cin.ignore(1000000, '\n');           // Clear cin so I can use getline.

	if (q_num == 2)
	{
		cout << "Name of the song: ";
		getline(cin, s_name);
		sender = GetQuery_9(szFee, s_name);
	}
	else if (q_num == 3)
	{
		cout << "Name of the song: ";
		getline(cin, s_name);
		sender = GetQuery_10(szFee, s_name);
	}
	else if (q_num == 4)
	{
		cout << "Name of the song: ";
		getline(cin, s_name);
		sender = GetQuery_15(szFee, s_name);
	}
	else
		sender = GetQuery_4(szFee);

	return sender;
}


//GENRES
string g_choice(char* szFee)
{
	int q_num = 0;
	string sender;

	string g_name = "";
	cout << "Enter the number corresponding with the information that you would like from the provided list: " << endl;
	cout << "1) All genre infromation" << endl;
	cout << "2) Number of songs in a given genre" << endl;
	cout << "3) Number of artists in a given genre" << endl;
	cout << "4) Number of albums in a given genre" << endl;
	cin >> q_num;

	cin.clear();
	cin.ignore(1000000, '\n');           // Clear cin so I can use getline.

	if (q_num == 2)
	{
		cout << "Genre: ";
		getline(cin, g_name);
		sender = GetQuery_11(szFee, g_name);
	}
	else if (q_num == 3)
	{
		cout << "Genre: ";
		getline(cin, g_name);
		sender = GetQuery_12(szFee, g_name);
	}
	else if (q_num == 4)
	{
		cout << "Genre: ";
		getline(cin, g_name);
		sender = GetQuery_16(szFee, g_name);
	}
	else
		sender = GetQuery_3(szFee);

	return sender;
}

// *****************************************USER CHOICES***************************************************




// ************************BEGIN ARTISTS QUERIES***********************************

// ALL ARTIST INFORMATION
string GetQuery_1(char* szFee) {

	string stSQL = "SELECT * ";
	stSQL += "FROM Artists ar ";
	stSQL += "ORDER BY ar.ArtistID ";

	return stSQL;
}


// NUMBER OF ALBUMS BY ARTIST
string GetQuery_5(char* szFee, string a_n) {

	string stSQL = "SELECT COUNT(al.AlbumID) ";
	stSQL += "FROM Artists ar, Albums al ";
	stSQL += "WHERE ar.ArtistID = al.ArtistID AND ar.[Artist Name] = ";
	stSQL += "'" + a_n + "' ";

	return stSQL;
}


// NUMBER OF SONGS BY ARTIST
string GetQuery_6(char* szFee, string a_n) {

	string stSQL = "SELECT COUNT(so.SongID) ";
	stSQL += "FROM Artists ar, Songs so ";
	stSQL += "WHERE ar.ArtistID = so.[Artist ID] AND ar.[Artist Name] = ";
	stSQL += "'" + a_n + "' ";

	return stSQL;
}


// ALL SONGS BY ARTIST
string GetQuery_13(char* szFee, string a_n) {

	string stSQL = "SELECT so.[Song Title] ";
	stSQL += "FROM Artists ar, Songs so ";
	stSQL += "WHERE ar.ArtistID = so.[Artist ID] AND ar.[Artist Name] = ";
	stSQL += "'" + a_n + "' ";

	return stSQL;
}


// ALL ALBUMS BY ARTIST
string GetQuery_14(char* szFee, string a_n) {

	string stSQL = "SELECT al.AlbumName ";
	stSQL += "FROM Artists ar, Albums al ";
	stSQL += "WHERE ar.ArtistID = al.ArtistID AND ar.[Artist Name] = ";
	stSQL += "'" + a_n + "' ";

	return stSQL;
}


// **************************END ARTISTS QUERIES***********************************





// *************************BEGIN ALBUMS QUERIES***********************************

// ALL ALBUM INFORMATION
string GetQuery_2(char* szFee) {

	string stSQL = "SELECT * ";
	stSQL += "FROM Albums ";
	stSQL += "ORDER BY AlbumID ";

	return stSQL;
}


// NUMBER OF SONGS/TRACKS ON AN ALBUM
string GetQuery_7(char* szFee, string al_n) {

	string stSQL = "SELECT COUNT(tr.[Track ID]) ";
	stSQL += "FROM Albums al, Tracks tr, Songs so ";
	stSQL += "WHERE tr.[Album ID] = al.AlbumID AND tr.[Song ID] = so.SongID AND al.AlbumName = ";
	stSQL += "'" + al_n + "' ";

	return stSQL;
}


// ALL SONGS/TRACKS ON AN ALBUM
string GetQuery_8(char* szFee, string al_n) {

	string stSQL = "SELECT so.[Song Title] ";
	stSQL += "FROM Albums al, Tracks tr, Songs so ";
	stSQL += "WHERE tr.[Album ID] = al.AlbumID AND tr.[Song ID] = so.SongID AND al.AlbumName = ";
	stSQL += "'" + al_n + "' ";

	return stSQL;
}

// ***************************END ALBUMS QUERIES***********************************





// **************************BEGIN SONGS QUERIES***********************************

// ALL SONG INFORMATION
string GetQuery_4(char* szFee) {

	string stSQL = "SELECT * ";
	stSQL += "FROM Songs ";

	return stSQL;
}


// SONG TITLE AND ARTIST NAME
string GetQuery_9(char* szFee, string s_n) {

	string stSQL = "SELECT so.[Song Title], a.[Artist Name] ";
	stSQL += "FROM Artists a, Songs so ";
	stSQL += "WHERE a.ArtistID = so.[Artist ID] AND so.[Song Title] = ";
	stSQL += "'" + s_n + "' ";

	return stSQL;
}


// SONG TITLE AND ALBUM NAME
string GetQuery_10(char* szFee, string s_n) {

	string stSQL = "SELECT so.[Song Title], al.AlbumName ";
	stSQL += "FROM Albums al, Songs so, Tracks tr ";
	stSQL += "WHERE al.AlbumID = tr.[Album ID] AND so.SongID = tr.[Song ID] AND so.[Song Title] = ";
	stSQL += "'" + s_n + "' ";

	return stSQL;
}


// SONG TITLE AND GENRE
string GetQuery_15(char* szFee, string s_n) {

	string stSQL = "SELECT so.[Song Title], g.Genre ";
	stSQL += "FROM Genre g, Songs so ";
	stSQL += "WHERE so.[Genre ID] = g.GenreID AND so.[Song Title] = ";
	stSQL += "'" + s_n + "' ";

	return stSQL;
}

// ****************************END SONGS QUERIES***********************************





// **************************BEGIN GENRE QUERIES***********************************

// ALL GENRE INFORMATION
string GetQuery_3(char* szFee) {

	string stSQL = "SELECT * ";
	stSQL += "FROM Genre ";

	return stSQL;
}


// NUMBER OF SONGS IN A GENRE
string GetQuery_11(char* szFee, string g_n) {

	string stSQL = "SELECT COUNT(so.SongID) ";
	stSQL += "FROM Genre g, Songs so ";
	stSQL += "WHERE so.[Genre ID] = g.GenreID AND g.Genre = ";
	stSQL += "'" + g_n + "' ";

	return stSQL;
}


// NUMBER OF ARTISTS IN A GENRE
string GetQuery_12(char* szFee, string g_n) {

	string stSQL = "SELECT COUNT(a.ArtistID) ";
	stSQL += "FROM Genre g, Songs so, Artists a ";
	stSQL += "WHERE so.[Artist ID] = a.ArtistID AND so.[Genre ID] = g.GenreID AND g.Genre = ";
	stSQL += "'" + g_n + "' ";

	return stSQL;
}


// NUMBER OF ALBUMS IN A GENRE
string GetQuery_16(char* szFee, string g_n) {

	string stSQL = "SELECT COUNT(al.AlbumID) ";
	stSQL += "FROM Genre g, Songs so, Tracks t, Albums al ";
	stSQL += "WHERE so.[Genre ID] = g.GenreID AND so.SongID = t.[Song ID] AND t.[Album ID] = al.AlbumID AND  g.Genre = ";
	stSQL += "'" + g_n + "' ";

	return stSQL;
}

// ****************************END GENRE QUERIES***********************************



