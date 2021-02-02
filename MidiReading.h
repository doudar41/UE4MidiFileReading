// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/FileHelper.h"
#include "GameFramework/Actor.h"
#include "HAL/Platform.h"
#include "MidiReading.generated.h"


USTRUCT(BlueprintType)
struct FTempoBytesArray
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintReadWrite, Category = "MidiNotesValues")
	TArray <uint8> NoteOns;
	UPROPERTY(BlueprintReadWrite, Category = "MidiNotesValues")
	TArray <uint8> NoteOffs;
	UPROPERTY(BlueprintReadWrite, Category = "MidiNotesValues")
	TArray <int32> DeltaTimes;
	UPROPERTY(BlueprintReadWrite, Category = "MidiNotesValues")
	TArray <uint8> NotePitches;
	UPROPERTY(BlueprintReadWrite, Category = "MidiNotesValues")
	int32 TickPerQuarter;

};

UCLASS()
class TESTMIDIANDLOOPS_API AMidiReading : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMidiReading();


	UFUNCTION(BlueprintCallable, Category = "File I/O")
	static TArray <uint8> LoadMidiFileToArray(FString filename);
	
	UFUNCTION(BlueprintCallable, Category = "Math")
	static FString BytesToHexFixed( uint8 In, int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Math")
		static FString BytesToCharFixed(uint8 In, int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Math")
		static FString BytesToBinaryStringFixed(uint8 In, int32 Count);
	
	UFUNCTION(BlueprintCallable, Category = "Math")
		static int32 AddingBytes(uint8 Byte1, uint8 Byte2, uint8 Byte3);

	 UFUNCTION(BlueprintCallable, Category = "Midi")
	 static FTempoBytesArray  MidiReadStruct(FString filename);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
