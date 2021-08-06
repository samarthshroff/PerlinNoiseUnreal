// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldCreator.h"
#include "PerlinNoiseComponent.h"
#include "Kismet/GameplayStatics.h"
#include "KismetProceduralMeshLibrary.h"

DEFINE_LOG_CATEGORY(PerlinNoiseWorldLogs)

// Sets default values for this component's properties
UWorldCreator::UWorldCreator()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;	
}


// Called when the game starts
void UWorldCreator::BeginPlay()
{
    Super::BeginPlay();
    this->proceduralMesh = Cast<UProceduralMeshComponent>(this->GetOwner()->GetComponentByClass(UProceduralMeshComponent::StaticClass()));
    this->perlinNoise = Cast<UPerlinNoiseComponent>(this->GetOwner()->GetComponentByClass(UPerlinNoiseComponent::StaticClass()));

    this->CreateWorld();
}

void UWorldCreator::CreateWorld()
{
    TArray<FVector> vertices;
    TArray<int32> triangles;
    TArray<FVector2D> uvs;
    FOccluderVertexArray normals;
    TArray<FColor> vertexColors;
    TArray<FProcMeshTangent> tangents;

    if (this->NumberOfVertsInX < 2) this->NumberOfVertsInX = 2;
    if (this->NumberOfVertsInY < 2) this->NumberOfVertsInY = 2;

    int64 universalArraySize = this->NumberOfVertsInX * this->NumberOfVertsInY;

    vertices.Empty();
    triangles.Empty();
    uvs.Empty();
    normals.Empty();

    tangents.Empty();


    UKismetProceduralMeshLibrary::CreateGridMeshWelded(this->NumberOfVertsInX, this->NumberOfVertsInY, triangles, vertices, uvs, this->GridSpacing);

    for (int64 i = 0; i < vertices.Num(); ++i)
    {
        int64 x = i / this->NumberOfVertsInX;
        int64 y = i % this->NumberOfVertsInX;

        float result = perlinNoise->GetValue((x * this->NoiseInputMultiplier) + 0.1, (y * this->NoiseInputMultiplier) + 0.1, 1.0); // We have to add 0.1 because the noise function doesn't work with integers
        result *= this->MaxHeight;

        vertices[i].Z = result;
    }

    UKismetProceduralMeshLibrary::CalculateTangentsForMesh(vertices, triangles, uvs, normals, tangents);
    vertexColors.Empty(vertices.Num());

    proceduralMesh->CreateMeshSection(0, vertices, triangles, normals, uvs, vertexColors, tangents, true);

    int64 index = 0;
    for (UMaterialInstance* mat : this->material)
    {
        proceduralMesh->SetMaterial(index++, mat);
    }
}

int64 UWorldCreator::GetIndexForGridCoods(int64 x, int64 y, int64 totalSamplesPerRow)
{
    return x + (y * totalSamplesPerRow);
}
