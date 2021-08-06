// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinNoiseComponent.h"

// Sets default values for this component's properties
UPerlinNoiseComponent::UPerlinNoiseComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the component is initialized
void UPerlinNoiseComponent::InitializeComponent()
{
	Super::InitializeComponent();

	this->_perlinNoise.SetFrequency(this->_frequency);
	this->_perlinNoise.SetLacunarity(this->_lacunarity);

	noise::NoiseQuality nq = static_cast<noise::NoiseQuality>((int32)this->_noiseQuality);
	this->_perlinNoise.SetNoiseQuality(nq);
	this->_perlinNoise.SetOctaveCount(this->_octaveCount);
	this->_perlinNoise.SetPersistence(this->_persistence);

	if (generateRandomSeed)
	{
		this->CreateRandomSeed();
	}
}

void UPerlinNoiseComponent::CreateRandomSeed()
{
	this->SetSeed(FMath::RandRange(0, INT32_MAX));
}

// Called when the game starts
void UPerlinNoiseComponent::BeginPlay()
{
	Super::BeginPlay();
}

#pragma region Getters
float UPerlinNoiseComponent::GetFrequency() const
{
	return this->_frequency;
}

float UPerlinNoiseComponent::GetLacunarity() const
{
	return this->_lacunarity;
}

PerlinNoiseQuality UPerlinNoiseComponent::GetNoiseQuality() const
{
	return this->_noiseQuality;
}

int32 UPerlinNoiseComponent::GetOctaveCount() const
{
	return this->_octaveCount;
}

float UPerlinNoiseComponent::GetPersistence() const
{
	return this->_persistence;
}

int32 UPerlinNoiseComponent::GetSeed() const
{
	return this->_seed;
}

#pragma endregion Getters

#pragma region Setters
void UPerlinNoiseComponent::SetFrequency(float frequency)
{
	this->_frequency = frequency;
	this->_perlinNoise.SetFrequency(frequency);
}

void UPerlinNoiseComponent::SetLacunarity(float lacunarity)
{
	this->_lacunarity = lacunarity;
	this->_perlinNoise.SetLacunarity(lacunarity);
}

void UPerlinNoiseComponent::SetNoiseQuality(PerlinNoiseQuality noiseQuality)
{
	this->_noiseQuality = noiseQuality;
	noise::NoiseQuality nq = static_cast<noise::NoiseQuality>((int32)noiseQuality);
	this->_perlinNoise.SetNoiseQuality(nq);
}

void UPerlinNoiseComponent::SetOctaveCount(int32 octaveCount)
{
	this->_octaveCount = octaveCount;
	this->_perlinNoise.SetOctaveCount(octaveCount);
}

void UPerlinNoiseComponent::SetPersistence(int32 persistence)
{
	this->_persistence = persistence;
	this->_perlinNoise.SetPersistence(persistence);
}

void UPerlinNoiseComponent::SetSeed(int32 seed)
{
	this->_seed = seed;
	this->_perlinNoise.SetSeed(seed);
}
#pragma endregion Setters

float UPerlinNoiseComponent::GetValue(float x, float y, float z) const
{
	return this->_perlinNoise.GetValue(x, y, z);
}

float UPerlinNoiseComponent::GetValueWithVector(FVector position) const
{
	return this->GetValue(position.X, position.Y, position.Z);
}


