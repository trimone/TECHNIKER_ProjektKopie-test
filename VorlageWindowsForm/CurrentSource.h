#pragma once

#include <vector>
//using namespace std;
using namespace System;

ref class CurrentSource
{

private:
	String^ deviceName;
	String^ deviceType;
	String^ serialNumber;
	bool polarity;	// 1 = Bipolar
	int maxCur;
	int maxV;
	double actCurrent;
	double frequency;
	double amplitude;
	int phase;
	String^ port;
	bool enable;
	static int count = 0;
	//array <wchar_t>^ BCS;// = gcnew array <wchar_t, 1>(3);

	   	 

public:
	CurrentSource()
	{
		count++;

		deviceName = "Current Source " + Convert::ToString(count);
		//deviceName = "Current Source " , count + 1;
		deviceType = "BCS 3/12";
		serialNumber = "-";
		polarity = 1;
		maxCur = 3;	// +/-
		maxV = 12;
		actCurrent = 0.0;
		frequency = 0;
		amplitude = 0;
		phase = 0;
		port = "COM " + Convert::ToString(99+count);
		enable = false;


	}
	CurrentSource(String^ id)
	{
		
		count++;		
		deviceName = "Current Source " + Convert::ToString(count);
		/// deviceName = "Current Source " + (count);			// => testen ob gehen tut !!!
		/// deviceName = "Current Source " + (char)(count);

		int id_cur_size;
		int id_length = id->Length;
        /*
		BCS = gcnew array <wchar_t, 1>(6); /// was war den das nochma !!!
		
		id->CopyTo(2, BCS, 0 ,3);*/

		// ID Struktur
		// "HighFinesse BCS3/12 S/N1121347-20181212\r"
		// "HighFinesse BCS255/255 S/N4294967295-20181212\r"

		// Polatität überprüfen
		if (id->Contains("BCS"))
		{
			polarity = 1;	// bipolar
		}
		else //if (id->Contains("UCS"))
			polarity = 0;	// unipolar


		std::vector <char> v_current;	// 'vector' = array liste // dynamisch erweiterbar mit '.pushback();'
								// WIKI: https://github.com/trimone/TechnikerProjekt_GUI/wiki/Dynamische-Arrays-(std::vector)#l
									//[Verwendung von Standard Template Library(STL)]
									/*
										=> std::vector <TYPE> var
										'vector' = array liste -> dynamisch erweiterbar mit '.pushback();'

										'vector' Datenstruktur wie 'array', Elemente liegen hintereinander im RAM.
										Elemente können an jeder Stelle hinzugefügt werden und enfernt werden.
										Zugrieff auf beliebige Elemente über einen Index [i].
									*/															
									//[DEBUGGING]
									/*
										'Mixes/ Gemischt' bei Debugger-Typ einstellen, sonst ist es nicht möglich Inhalt zu beobachten
											=> 'HF_GUI_Stromqelle' => RM 
											=> [EINGENSCHAFTEN] -> [Konfigurationseingenschaften] -> [Debugging] 
											-> [Debuggingtyp] => Gemischt (vorher war 'Automatisch' eingestellt)
										*/

	

		//int length = id->Length;
		//String^ test;
		//test = "SD";
		//array <wchar_t^>^ temp;//= gcnew array <wchar_t^> (1);

		//for (int i = 15; i < length ; i++)
		for (int i = 15; i < id_length; i++)	// 'i = 15' Startposition in ID, da "HighFinesse" nicht benötigt wird
		{
			while (id[i] != '/')	// Loop solange '/' nicht erreicht wurde & Werte in vector speichern
			{
				
				//temp->Resize(temp, j + 1);
				//test->Resize(test, j + 1);
				//rest[i] = 'E';
				//test=test->Insert(0, id[i]);
				
				//temp.resize(1);		// Mixed Debuging einstellen ??? 
									/* */
				//temp.push_back( id[i]);	// es wird eine Kopie erstellt, nicht optimal

				v_current.emplace_back(id[i]);	// neuen Wert in vector speichern dynamisch vergrößern  
												// Optimierung von '.push_back()'
				i++;

				
				//maxCur += Convert::totemp[i];
			}

			// Gefundenen max Strom in 'int maxCur' speichern
			id_cur_size = (v_current.size());	// size of vector in Variable speichern
			if (id_cur_size > 1)				// wenn max Strom mehrstellig zB. 'BSC100/..'
			{
				// Rehefolge der Elemente im vector umdrehen für Potenzrechnung
				std::reverse(v_current.begin(), v_current.end());	// falls auch zweistellig !!	
				// starten mit einer Stelle, [i++] * 10 entspricht Zehner Stelle usw... 
				for (int i = 0, potency = 1; i < v_current.size(); i++, potency *= 10)
				{
					maxCur = maxCur + ((v_current[i] - 0x30) * potency);
					//p *= 10;
				}

				v_current.clear();	// vector leeren, size = 0
			}

			// wenn max Strom einstellig 
			else if (!v_current.empty())	/// 'else if' wirklich noctwendig ?!
			{
				maxCur += (v_current[0] - 0x30);
			}

			/// es wird eine Art break; benötigt
			/// 'v_current'-vector evtl noch löschen !!!
			
			
				
			//test = temp.;
		}

		/*polarity = 1;
		if (BCS[0] != 'B')
		{
			polarity = 0;
		}*/


		actCurrent = 0.0;
		frequency = 0;
		amplitude = 0;
		phase = 0;

		/// COM Port setzen !!!
		port = "COM " + Convert::ToString(99 + count);
		enable = false;

	}
	~CurrentSource()
	{
		count--;
	}
/*
	String^ getName()
	{
		return (deviceName);
	}
	void setName(String^ name)
	{

	}
	String^ getType()
	{

	}
	///<summary> Liefert Serienmummer </summary>
	String^ getSN()
	{

	}
	bool getPolarity()
	{

	}
	double getMaxCur()
	{

	}
	void setCur(double cur)
	{

	}
	double getCur()
	{

	}
	void setFreq(double freq)
	{

	}
	double getFreq()
	{

	}
	void setAmp(double amplitude)
	{

	}
	double getAmp()
	{

	}
	void setPhase(int phase)
	{

	}
	int getPhase()
	{

	}
	void setPort(String^ port)
	{

	}
	String^ getPort()
	{

	}
	void enable()
	{

	}
	void disable()
	{

	}
	*/
	static int getCount()
	{
		return count;
	}
};

