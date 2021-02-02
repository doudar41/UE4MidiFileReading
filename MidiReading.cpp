// Fill out your copyright notice in the Description page of Project Settings.


#include "MidiReading.h"
#include <Misc/Paths.h>
#include "Containers/UnrealString.h"
#include <HAL/PlatformFilemanager.h>

#define LINE_TERMINATOR

// Sets default values
int Number = 0;


AMidiReading::AMidiReading()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMidiReading::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Something"));
}



// ================These are utilities to convert byte to strings======

FString AMidiReading::BytesToHexFixed(uint8 In, int32 Count)
{
	const uint8* InPointer = &In;
	FString Broken = BytesToHex(InPointer, Count);

	return Broken;
}

FString AMidiReading::BytesToCharFixed(uint8 In, int32 Count)
{
	const uint8* InPointer = &In;
	FString ToString = BytesToString(InPointer, Count);
	FString Fixed;

	for (int i = 0; i < ToString.Len(); i++)
	{
		const TCHAR c = ToString[i] - 1;
		Fixed.AppendChar(c);
	}

	return Fixed;
}

FString AMidiReading::BytesToBinaryStringFixed(uint8 In, int32 Count)
{
	FString Output;
	int temp = In;

	for (int i = 0; i < Count; i++)
	{
		int temp2;
		temp2 = temp % 2;
		Output.Append(FString::FromInt(temp2));
		temp = temp / 2;
	}
	Output.ReverseString();

	return Output;
}

// =================This function loads Midi file to array of bytes ================

TArray <uint8> AMidiReading::LoadMidiFileToArray(FString filename)
{
	FString directory = FPaths::ProjectContentDir();
	TArray <uint8> result;

	IPlatformFile& midifile = FPlatformFileManager::Get().GetPlatformFile();
	if (midifile.CreateDirectory(*directory))
	{
		FString MyFile = directory + "/" + filename;
		FFileHelper::LoadFileToArray(result, *MyFile);
	}

	return result;
}

// =================Reading microseconds to quarter tempo to use in calculation of BPM ================ 

int32 AMidiReading::AddingBytes(uint8 Byte1, uint8 Byte2, uint8 Byte3)
{
	int32 tempo;

	BYTE byte1 = Byte1;
	BYTE byte2 = Byte2;
	BYTE byte3 = Byte3;

	tempo = byte1 << 16 | byte2 << 8 | byte3;

	return tempo;
}


// ================= Reading midi file notes durations, pitches, delta time out them in arrays ========

FTempoBytesArray AMidiReading::MidiReadStruct(FString filename)
{


	FTempoBytesArray notes;
	TArray <uint8> In = LoadMidiFileToArray(filename);
	uint8 nValue = 0; 
	uint32_t ResultValue = 0;
	uint8 nByte = 0;
	int count = 1;
	int32 ThirtyTwoValue;
	int32 Bar =0;

	ResultValue = In[12];
	ResultValue &= 0x7F;
	nByte = In[12 + 1];
	ResultValue = ResultValue << 8 | nByte ;

	notes.TickPerQuarter = ResultValue;

	ThirtyTwoValue = notes.TickPerQuarter / 8;




	for (int i = 0; i < In.Num(); i++)
	{
		ResultValue = In[i];
		if (ResultValue & 0x80)
		{
			ResultValue &= 0x7F;
			count = 1;
			do
			{
				nByte = In[i + count];

				ResultValue = (ResultValue << 7) | (nByte & 0x7F);
				count++;
			} while (nByte & 0x80);

			nValue = In[i + count];
			if (nValue == 0x90 || nValue == 0x80)
			{
				notes.DeltaTimes.Add(ResultValue);

				if (nValue == 0x90){notes.NoteOns.Add(In[i + count]); }
				
				if (nValue == 0x80) { notes.NoteOffs.Add(In[i + count]); }
				
				notes.NotePitches.Add(In[i + count + 1]);
			}
		}
	}

	return notes;
}




// Called every frame
void AMidiReading::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

