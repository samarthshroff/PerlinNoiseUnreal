// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProceduralMeshComponent.h"
#include "WorldCreator.generated.h"

class AActor;
class UPerlinNoiseComponent;

DECLARE_LOG_CATEGORY_EXTERN(PerlinNoiseWorldLogs, Log, All)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERLINNOISEWORLD_API UWorldCreator : public UActorComponent
{
    GENERATED_BODY()

public:	
    // Sets default values for this component's properties
    UWorldCreator();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:	
    UPROPERTY(EditAnywhere)
        TArray<UMaterialInstance*> material;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Generation Values", meta = (Tooltip = "Number of vertices in X. Defaults to 2."))
        int64 NumberOfVertsInX = 2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Generation Values", meta = (Tooltip = "Number of vertices in Y. Defaults to 2."))
        int64 NumberOfVertsInY = 2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Generation Values", meta = (Tooltip = "Size of each quad in world units."))
        float GridSpacing;

    UPROPERTY(EditAnywhere, Category = "Mesh Generation Values", meta = (Tooltip = "Smaller the value the more the perlin noise terrain will stretch. The perlin noise function returns values between -1 to 1 which won't be really visible thus need to have a multiplier."))
        float NoiseInputMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Generation Values", meta = (Tooltip = "Greater the value the more the terrain's height scales."))
        float MaxHeight;

    int64 GetIndexForGridCoods(int64 x, int64 y, int64 totalSamplesPerRow);

private:
    UFUNCTION(BlueprintCallable)
        void CreateWorld();

    UProceduralMeshComponent* proceduralMesh;
    UPerlinNoiseComponent* perlinNoise;
};