#include <iostream>
#include <string>

void kysyVuodenaika();

int main()
{
	kysyVuodenaika();

	////kevät
	//else if ()
	//{

	//}

	////kesä 
	//else if ()
	//{

	//}

	////syksy
	//else
	//{

	//}


	system("PAUSE");
	//var vuodenajat = ["tammi", "helmi", "maalis"];
	//var syote;
	
	
	//1. kysytään käyttäjältä vuodenaika
	//2. tallennetaan arvo syote muuttujaan
	//3. etsitaan vuodenajat taulukosta vastaava vuodenaika
	//4. näytetään käyttäjälle löydetty vuodenaika


	//= vuodenajat[0];

	/*
	*
	*
	*
	*
	*
	*
	*
	*
	*
	*
	*
	*/
	

	for (int x = 0; x < 10; x++)
	{

	}

	int i = 0;

	while (i < 10)
	{
		int arvo = 0;
	}


	//var x; 
	//var elain;

	int x = 0;
	std::string elain = "koira";

	while (elain == "kissa")
	{
		x++;
		if (x > 3)
		{
			elain = "koira";
		}
	}

	std::string eläin = "";
	int y = 0;

	do
	{
		y++;
	} 
	while (y < 3);



	return 0;
}

void kysyVuodenaika()
{

	int vuodenaika;

	std::cout << "anna kuukausi" << std::endl;
	std::cin >> vuodenaika;

	//
	std::string veriryhma[4] = { "A+", "A-", "B+", "O-" };
	//std::string veriryhma[4] = { [0],  [1],   [2],  [3] };

	for (size_t i = 0; i < 9; i++)
	{
		veriryhma[0] == "A+";
		veriryhma[1] == "A-";
		veriryhma[2] == "B+";
	}


	//talvi
	if ((0 < vuodenaika) && (vuodenaika < 3 || vuodenaika == 12))
	{
		std::cout << "talvi" << std::endl;
		kysyVuodenaika();

	}
	else
	{
		kysyVuodenaika();
	}
}