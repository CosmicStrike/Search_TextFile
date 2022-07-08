
//Version 2.0 Update

#include<iostream>
#include<iomanip>
#include<fstream>
#include<thread>
#include<vector>
#include<set>
#include<conio.h>

//BacckGround Thread 1 Performs the task to order the file names and words enter by user
bool BackGroundThread1(const std::string& FileToOverWriteName, std::vector<std::string>& PreviousFileNames)
{
	char cBuffer = ' ';
	std::string Str_Buffer;
	std::fstream fFile;
	fFile.open(FileToOverWriteName.c_str(), std::ios_base::ate|std::ios_base::in);
	if (!fFile)
	{
		std::cout << std::endl;
		std::cout << "File Cannot Be Opened To Write   -> " << FileToOverWriteName;
		std::cout << std::endl;
		return false;
	}

	std::set<std::string> SortedNames;

	fFile.seekg(0, std::ios_base::beg);
	cBuffer = fFile.get();
	if (cBuffer != '#')
	{
		std::cout << std::endl << "     File Is Empty     \n\n";
		std::cout << "    No Previous Entry Stored    " << std::endl;
		return false;
	}

	fFile.seekg(2, std::ios_base::beg);
	while (!fFile.eof())
	{
		fFile >> Str_Buffer;
		SortedNames.insert(Str_Buffer);
	}



	//std::cout << std::endl << "File Names Soretd " << std::endl;
	for (std::string Names : SortedNames)
	{
		PreviousFileNames.push_back(Names);
	}

	fFile.close();

	//std::cout << "\nSuccessfully Enter in Vector \n";

	fFile.open(FileToOverWriteName.c_str(), std::ios_base::trunc|std::ios_base::out|std::ios_base::in);
	if (!fFile)
	{
		std::cout << std::endl << "File Cannot Open to Rewrite    :  ";
		std::cout << std::endl;
		return false;
	}

	fFile << "#" << std::endl;

	for (int i = 0;i < PreviousFileNames.size();i++)
		fFile <<"  "<< PreviousFileNames[i] ;

	//std::cout <<std::endl<< "Successfully Written to the File Sorted Names     ";
	std::cout << std::endl;
	std::cout << std::endl;

	fFile.close();
	return true;
}




int main()
{
	long int OccuranceOfLiteral = 0;
	int iBuffer = 0;


	int i = 1;
	int ii = 1;
	int q = 1;

	char cBuffer = ' ';



	std::string Str_TextToSearch;
	std::string Str_CurrentFileName;
	const std::string Str_UnWantedCharacters = "\",.;:'<>?/!()~`[]{}|^";
	std::string Str_DatatFileNames = "DataBase1_FN.txt";
	std::string Str_DataWordsName = "DataBase2_WN.txt";
	std::string Str_Buffer;


	bool bPreviousFileOpen = false, bNewFileOPen = false;
	bool bPreviousWord = false, bNewWord = false;


	bool bOpenNewFile = false;

	bool bGotFile = false;

	bool value = false;

	bool bGotText = false;

	std::fstream fCurrentReadingFile;
	std::fstream fWordsFile, fPreviousFile;

	std::vector<std::ios::streamoff> vPositionOfCharacterInFile;
	std::vector<std::string> vStoredFileName;
	std::vector<std::string> vStoredWords;



	fPreviousFile.open(Str_DatatFileNames.c_str(), std::ios_base::out | std::ios_base::app);
	fWordsFile.open(Str_DataWordsName.c_str(), std::ios_base::out | std::ios_base::app);

	fPreviousFile.close();
	fWordsFile.close();

	bOpenNewFile = true;

	//Main While Loop so that to close or reset will know
	while (true)
	{
		MainPage:
		system("CLS");

		while (true)
		{
			if (bOpenNewFile)
			{
				if (q == 1)
				{
					std::cout << std::endl << std::setw(50) << " SEARCH.EXE  " << std::endl;
					std::cout << std::endl << std::endl;

					std::cout << std::setw(65) << " THIS PROGRAM IS FOR EDUCATIONAL PURPOSE   ";
					std::cout << std::endl;

					std::cout << std::endl << std::endl << std::endl;
					std::cout << std::setw(78) << "PROGRAM IS DEVELOPED BY     :    SHUBHAM CHANDRAKANT CHOUGULE    ";


					std::cout << std::endl << std::endl << std::endl << "LOADING................";


					std::this_thread::sleep_for(std::chrono::seconds(6));

					q++;
					system("CLS");
				}
				//Checks Whether OPen NEw File Or Existing File and other erasing data task

				system("CLS");

				//std::cout << std::endl << std::setw(80) << "Searching Program Developed by Shubham Chandrakant Chougule  ";

				std::cout<<std::endl<<"NOTICE    :     PLEASE ENTER WHITESPACE AT END OF TEXT FILE IF IT IS NOT THERE. ";
				std::cout << std::endl <<std::endl<< "THANK YOU ";

				std::cout << std::endl <<std::endl << std::endl<<std::endl;


				std::cout << std::setw(60) << "Choose the File opening Options    :  " << std::endl;
				std::cout << std::endl << "1.    Choose From Previously Opened Files   ->  Press   ('  p ') ";
				std::cout << std::endl << std::endl << "2.    Open New File   ->  Press  ('  n  ') ";
				std::cout << std::endl << std::endl << "3.    Erase All File Name Search Data    ->  Press  ('  z  ') ";
				std::cout << std::endl << std::endl << "4.    Erase All Text Search Data    ->  Press  ('  t  ') ";
				std::cout << std::endl << std::endl;
				std::cout << std::endl;
				std::cout << "  Enter   :   ->   ";
				std::cin >> cBuffer;

				if (cBuffer == 'n')
				{
					bPreviousFileOpen = false;
					bNewFileOPen = true;
					break;
				}
				else if (cBuffer == 'p')
				{
					bNewFileOPen = false;
					bPreviousFileOpen = true;
					break;
				}
				else if (cBuffer == 't')
				{
					fWordsFile.open(Str_DataWordsName.c_str(), std::ios_base::trunc | std::ios_base::in | std::ios_base::out);
					fWordsFile.close();
					
					std::cout << std::endl << "All Word Searches Data Eraseing";
					std::cout << std::endl << std::endl << "Please Wait";
					std::this_thread::sleep_for(std::chrono::seconds(4));
				}
				else if (cBuffer == 'z')
				{
					fPreviousFile.open(Str_DatatFileNames.c_str(), std::ios_base::trunc | std::ios_base::in | std::ios_base::out);
					fPreviousFile.close();
					std::cout << std::endl << "All File Open Data Eraseing";
					std::cout << std::endl << std::endl << "Please Wait";
					std::this_thread::sleep_for(std::chrono::seconds(4));
				}
				else
				{
					
					std::cout << std::endl << std::endl << "           =====   InValid Input Please Try Again   : =======";
					std::cout << std::endl << std::endl << "Please Wait";
					std::this_thread::sleep_for(std::chrono::seconds(4));

				}

				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');

			}
			//breaks if same file open again
			if (!bOpenNewFile)break;
		}

			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');


			//Takes File Name From User
			while (!bGotFile)
			{

				if (bNewFileOPen)
				{
					system("CLS");
					std::cout << std::endl << "Enter the file Name to Open  (characters less than 40) : ";

					char* pcFileName = new char[40];
					std::cin.getline(pcFileName, 39, '\n');
					Str_CurrentFileName = pcFileName;
					Str_CurrentFileName.append(".txt");
					delete[]pcFileName;



					fPreviousFile.open(Str_DatatFileNames.c_str(), std::ios_base::ate | std::ios_base::out | std::ios_base::in);

					if (fPreviousFile.tellp() <= 1 && fPreviousFile.tellg() <= 1)fPreviousFile << "#";

					fPreviousFile << "  " << Str_CurrentFileName;

					fPreviousFile.close();

					bGotFile = true;
				}
				else if (bPreviousFileOpen)
				{
					//Executes once BackGroundThread1 function
					//and resets i value when sam file open
					if (i == 1)
						value = BackGroundThread1(Str_DatatFileNames, vStoredFileName);

					i++;


					if (value)
					{
						while (true)
						{
							system("CLS");

							//displays the info in database file and shows to user
							std::cout << "Index No" << std::endl;
							std::cout << std::endl;
							for (int i = 0;i < vStoredFileName.size();i++)
								std::cout << std::endl << std::endl << i + 1 << ".        -            " << vStoredFileName[i];

							//takes corresponding number and error checking code
							std::cout << std::endl << std::endl << std::endl << "Choose Corresponding Index Number To Open The File     :    ";
							std::cin >> iBuffer;


							if (!std::cin)
							{
								std::cin.clear();
								std::cin.ignore(INT_MAX, '\n');
								std::cout << std::endl << "IT IS NOT THE NUMBER  !!!!!!!!" << std::endl;
								std::cout << std::endl << "Please Try Again ";
								std::cout << std::endl << std::endl << "Please Wait";
								std::this_thread::sleep_for(std::chrono::seconds(4));
							}
							else if (iBuffer <= vStoredFileName.size() && iBuffer > 0)
							{

								Str_CurrentFileName = vStoredFileName[iBuffer - 1];
								std::cout << std::endl << std::endl << "Press (' c ') Key To Confirm   \" " << Str_CurrentFileName << " \" File To Open    ";
								std::cout << std::endl << std::endl << "Or Any Other Key To ReChoose Another Index " << std::endl << std::endl;
								std::cout << std::endl << "Input Please   :   ";
								std::cin >> cBuffer;
								if (cBuffer == 'c')
								{
									fCurrentReadingFile.open(Str_CurrentFileName.c_str(), std::ios_base::in | std::ios_base::ate);
									if (!fCurrentReadingFile)
									{
										system("CLS");
										std::cout << std::endl << "=====================================";
										std::cout << std::endl << Str_CurrentFileName << " is Missing In The Current Directory " << std::endl;
										std::cout << std::endl << "   Try Another File  " << std::endl;
										std::cout << std::endl << "=====================================";
										std::cout << std::endl << std::endl << "Please Wait";
										std::this_thread::sleep_for(std::chrono::seconds(6));
									}
									else
									{
										bGotFile = true;
										fCurrentReadingFile.close();
										break;
									}
								}
								std::cin.clear();
								std::cin.ignore(INT_MAX, '\n');

							}
							else
							{
								std::cin.clear();
								std::cin.ignore(INT_MAX, '\n');
								std::cout << std::endl << "OUT OF RANGE  !!!!!!!!" << std::endl;
								std::cout << std::endl << "Please Try Again ";
								std::cout << std::endl << std::endl << "Please Wait";
								std::this_thread::sleep_for(std::chrono::seconds(4));
							}


						}
					}
					else
					{
						std::cout << std::endl << std::endl << "     Error ocured in Data Management Process i.e File Is Empty   " << std::endl;
						std::cout << std::endl << std::endl << "Please Wait";
						std::this_thread::sleep_for(std::chrono::seconds(4));
						goto MainPage;
					}

				}
			
			}


		system("CLS");


		//open the file
		fCurrentReadingFile.open(Str_CurrentFileName.c_str(), std::ios_base::in | std::ios_base::ate);

		if (!fCurrentReadingFile)
		{
			std::cout << std::endl << "=====================================";
			std::cout << std::endl << Str_CurrentFileName << " is Missing In The Current Directory " << std::endl;
			std::cout << std::endl << "   Try Another File  " << std::endl;
			std::cout << std::endl << "=====================================";
			std::cout << std::endl << std::endl << "Please Wait";
			bGotFile = false;
			std::this_thread::sleep_for(std::chrono::seconds(8));

		}
		else
		{
			//get new word or from previous words
			while (!bGotText)
			{
				system("CLS");

				std::cout << std::endl << "===================================" << std::endl;

				std::cout << std::endl << "        File Opened Successfully" << std::endl;
				std::cout << std::endl << "===================================" << std::endl;
				std::cout << std::endl;
				std::cout << std::endl;
				std::cout << std::endl;
				//std::cout << std::endl << "Program Will Not Find The Text Ending With FULLSTOP (' . ')   ";
				//std::cout << std::endl;
				//std::cout << std::endl;

				std::cout << std::endl << "Want To Enter New Word   ->   Enter   '  n  '       ";
				std::cout << std::endl;
				std::cout << std::endl;
				std::cout << std::endl << "Want To Choose From Previously Searched Word  ->   Enter   '  p  '   ";
				std::cout << std::endl;
				std::cout << std::endl;
				std::cout << "Please Enter    ->       :  ";

				std::cin >> cBuffer;

				if (cBuffer == 'n')
				{

					bNewWord = true;
					bPreviousWord = false;
					std::cout << std::endl << std::endl << std::endl << "Please Enter  the Text To Search :  ";
					std::cin >> Str_TextToSearch;

					fWordsFile.open(Str_DataWordsName.c_str(), std::ios_base::out | std::ios_base::in | std::ios_base::ate);

					if (!fWordsFile)std::cout << std::endl << std::endl << "Cannot Open File Containing Previously Searched Words" << std::endl;
					else
					{
						if (fWordsFile.tellp() <= 1 && fWordsFile.tellg() <= 1)fWordsFile << "# " << std::endl;
						fWordsFile << "   " << Str_TextToSearch;
						fWordsFile.close();
					}

					break;

				}

				else if (cBuffer == 'p')
				{
					if (ii == 1)
						value = BackGroundThread1(Str_DataWordsName, vStoredWords);

					ii++;


					if (value)
					{
						while (true)
						{
							system("CLS");


							std::cout << "Index No" << std::endl;
							std::cout << std::endl;
							for (int i = 0;i < vStoredWords.size();i++)
								std::cout << std::endl << std::endl << i + 1 << ".        -            " << vStoredWords[i];


							std::cout << std::endl << std::endl << std::endl << "Choose Corresponding Index Number To Open The File     :    ";
							std::cin >> iBuffer;


							if (!std::cin)
							{
								std::cin.clear();
								std::cin.ignore(INT_MAX, '\n');
								std::cout << std::endl << "IT IS NOT THE NUMBER  !!!!!!!!" << std::endl;
								std::cout << std::endl << "Please Try Again ";
								std::cout << std::endl << std::endl << "Please Wait";
								std::this_thread::sleep_for(std::chrono::seconds(4));
							}
							else if (iBuffer <= vStoredWords.size() && iBuffer > 0)
							{

								Str_TextToSearch = vStoredWords[iBuffer - 1];
								std::cout << std::endl << std::endl << "Press (' c ') Key To Confirm   \" " << Str_TextToSearch << " \" Word To Search    ";
								std::cout << std::endl << std::endl << "Or Any Other Key To ReChoose Another Index " << std::endl << std::endl;
								std::cout << std::endl << "Input Please   :   ";
								std::cin >> cBuffer;
								if (cBuffer == 'c')
								{
									//std::cin.ignore(INT_MAX, 'n');
									bGotText = true;
									break;
								}
								else
								{
									std::cin.ignore(INT_MAX, '\n');
								}

							}
							else
							{
								std::cin.clear();
								std::cin.ignore(INT_MAX, '\n');
								std::cout << std::endl << "OUT OF RANGE  !!!!!!!!" << std::endl;
								std::cout << std::endl << "Please Try Again ";
								std::cout << std::endl << std::endl << "Please Wait";
								std::this_thread::sleep_for(std::chrono::seconds(4));
							}

						}
					}
					else
					{
						std::cout << std::endl << std::endl << "        Error ocured in Data Management Process i.e File Is Empty   " << std::endl;
						std::cout << std::endl << std::endl << "Please Wait";
						std::this_thread::sleep_for(std::chrono::seconds(6));

					}



				}
				else
				{
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');

					std::cout << std::endl << "INVALID INPUT.......................PLEASE TRY AGAIN";
					std::cout << std::endl << std::endl << "Please Wait";
					std::this_thread::sleep_for(std::chrono::seconds(4));
				}

			}


		}
		//if file open then do searching
		//this is here because no while loop exist to retake file name which does not exits in directory
		//but i have check for validity of file in pervious file choosing and new file chooseing
		if (fCurrentReadingFile)
		{
			fCurrentReadingFile.seekg(0, std::ios_base::beg);

			//this is here because to read from file the words and get the corresponding
			//location of that word and store it in vector
			//so that ahead file open in out mode can write | chara in that place
			while (!fCurrentReadingFile.eof())
			{
				fCurrentReadingFile >> Str_Buffer;
	
				if (Str_TextToSearch == Str_Buffer)
				{
					OccuranceOfLiteral++;
					vPositionOfCharacterInFile.push_back(fCurrentReadingFile.tellg());
				}
				else if (Str_TextToSearch.size() > 1&&Str_Buffer.size()>1)
				{
					bool bDeleted = false;
					bool bGetOut = false;
					while (!bGetOut)
					{
						
						for (int i = 0;i < Str_UnWantedCharacters.size();i++)
						{
							if (Str_Buffer[0] != Str_UnWantedCharacters[i])bDeleted = false;

							if (Str_Buffer[Str_Buffer.size() - 1] != Str_UnWantedCharacters[i])bDeleted = false;

							if (Str_Buffer[0] == Str_UnWantedCharacters[i])
							{
								Str_Buffer.erase(0);
								bDeleted = true;
							}
							else if (Str_Buffer[Str_Buffer.size() - 1] == Str_UnWantedCharacters[i])
							{
								Str_Buffer.erase(Str_Buffer.size()-1);
								bDeleted = true;
							}
					
							
						}

						if (!bDeleted)bGetOut = true;
					}

					if (Str_TextToSearch == Str_Buffer)
					{
						OccuranceOfLiteral++;
						vPositionOfCharacterInFile.push_back(fCurrentReadingFile.tellg());
					}

				}
				Str_Buffer = "82yh784ghuy83yhuhfuh3hfhu";
			}
			fCurrentReadingFile.close();




			//open file to write | character at locations stored in vector
			fCurrentReadingFile.open(Str_CurrentFileName.c_str(), std::ios_base::out | std::ios_base::in | std::ios_base::ate);

			if (!fCurrentReadingFile)std::cout << "Canot Open T0 Rewrite   \n\n";
			else
			{
				fCurrentReadingFile.seekp(0, std::ios_base::beg);
				fCurrentReadingFile.seekg(0, std::ios_base::beg);
				for (int i = 0;i < vPositionOfCharacterInFile.size();i++)
				{
					fCurrentReadingFile.seekp(vPositionOfCharacterInFile[i], std::ios_base::beg);
					fCurrentReadingFile << "|";
				}
			}
			fCurrentReadingFile.close();

			//gives user chance to locate the word in text file so wait here until user puts input

			system("CLS");

			std::cout << std::endl << "The Text   \"  " << Str_TextToSearch << "  \" Has Occured     : " << OccuranceOfLiteral << "   Times " << std::endl;

			std::cout << std::endl << std::endl << "THIS PROGRAM WILL MAKE CHANGES IN   \"  " << Str_CurrentFileName << "   \"  TEXT FILE " << std::endl;
			std::cout << std::endl << "IT WILL  ENTER ' | ' CHARACTER AFTER THE   \"  " << Str_TextToSearch << "  \"   WORD  IF IT OCCUR's  " << std::endl;
			std::cout << std::endl << std::endl << "PLEASE CHECK TEXT FILE........  " << std::endl << std::endl;
			std::cout << std::endl << std::endl << "ENTER ANY KEY TO CONTINUE AND UNDO THE CHANGES IN TEXT FILE   " << std::endl;
			std::cin >> cBuffer;


			//again open file to delete | character from location stored in vector

			fCurrentReadingFile.open(Str_CurrentFileName.c_str(), std::ios_base::out | std::ios_base::in | std::ios_base::ate);
			if (!fCurrentReadingFile)std::cout << std::endl << "Canont Open Second Time   : \n";
			else
			{

				fCurrentReadingFile.seekp(0, std::ios_base::beg);
				fCurrentReadingFile.seekg(0, std::ios_base::beg);

				for (int i = 0;i < vPositionOfCharacterInFile.size();i++)
				{
					fCurrentReadingFile.seekp(vPositionOfCharacterInFile[i], std::ios_base::beg);
					fCurrentReadingFile << " ";
				}

			}
			fCurrentReadingFile.close();


			system("CLS");

			//Gives user chance to search again or to close

			std::cout << std::endl << std::endl << std::setw(40) << "To Close The Program   Press   '  c  '  ";
			std::cout << std::endl << std::endl << std::setw(40) << "Else   Press Any Button To Search Again  ";

			std::cout << "Input    ->   : ";
			std::cin >> cBuffer;

			if (cBuffer == 'c')break;
			else
			{
				while (true)
				{
					system("CLS");
					std::cout << std::endl << std::endl << std::setw(40) << "To Open Same File    Press   '  s  '  ";
					std::cout << std::endl << std::endl << std::setw(40) << "To Open New  File    Press   '  n  '  ";
					std::cout << std::endl << "Press    :  ";
					std::cin >> cBuffer;

					//resets the values to normal

					if (cBuffer == 's')
					{
						ii = 1;
						i = 1;
						bOpenNewFile = false;
						bGotFile = true;
						OccuranceOfLiteral = 0;
						vStoredFileName.clear();
						vStoredWords.clear();
						bGotText = false;
						vPositionOfCharacterInFile.clear();
						break;
					}
					else if (cBuffer == 'n')
					{
						ii = 1;
						bGotText = false;

						vStoredFileName.clear();
						vStoredWords.clear();

						vPositionOfCharacterInFile.clear();

						i = 1;
						OccuranceOfLiteral = 0;
						bOpenNewFile = true;
						bGotFile = false;
						value = false;
						bPreviousWord = false;
						bNewWord = false;
						bPreviousFileOpen = false;
						bNewFileOPen = false;
						break;
					}
					else
					{
						std::cin.clear();
						std::cin.ignore(INT_MAX, '\n');
						std::wcout << std::endl << ".............................PLEASE PRESS CORRECT KEY..........";
						std::cout << std::endl << std::endl << "Please Wait";
						std::this_thread::sleep_for(std::chrono::seconds(6));

					}
				}
			}
		}
	}
	return 0;
}

	//Program ends here

