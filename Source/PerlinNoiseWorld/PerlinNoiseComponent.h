// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <libnoise.h>
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PerlinNoiseComponent.generated.h"


UENUM(BluePrintType)
enum class PerlinNoiseQuality : uint8
{
    QUALITY_FAST    UMETA(DisplayName = "Fast Quality"),
    QUALITY_STD     UMETA(DisplayName = "Standard Quality"),
    QUALITY_BEST    UMETA(DisplayName = "Best Quailty")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PERLINNOISEWORLD_API UPerlinNoiseComponent : public UActorComponent
{
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere, Category = "Perlin Noise", meta = (Tooltip = "The frequency of the first octave."))
        float _frequency = 1.0;

    UPROPERTY(EditAnywhere, Category = "Perlin Noise", meta = (Tooltip = "Lacunarity is the frequency multiplier between successive octaves. For best results, set the lacunarity to a number between 1.5 and 3.5"))
        float _lacunarity = 2.5;

    UPROPERTY(EditAnywhere, Category = "Perlin Noise", meta = (Tooltip = "The quality of the Perlin noise."))
        PerlinNoiseQuality _noiseQuality = PerlinNoiseQuality::QUALITY_STD;

    UPROPERTY(EditAnywhere, Category = "Perlin Noise", meta = (Tooltip = "The number of octaves controls the amount of detail in the Perlin noise."))
        int32 _octaveCount = 15;

    UPROPERTY(EditAnywhere, Category = "Perlin Noise", meta = (Tooltip = "The persistence value controls the roughness of the Perlin noise.  For best results, set the persistence to a number between 0.0 and 1.0"))
        float _persistence = 0.5;

    UPROPERTY(EditAnywhere, Category = "Perlin Noise", meta = (Tooltip = "The seed value used by the Perlin-noise function.", EditCondition = "!generateRandomSeed"))
        int32 _seed = 0;

    noise::module::Perlin _perlinNoise;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    // Called when component is initialized
    virtual void InitializeComponent() override;

public:
    // Sets default values for this component's properties
    UPerlinNoiseComponent();

#pragma region Getters
    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        float GetFrequency() const;

    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        float GetLacunarity() const;

    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        PerlinNoiseQuality GetNoiseQuality() const;

    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        int32 GetOctaveCount() const;

    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        float GetPersistence() const;

    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        int32 GetSeed() const;
#pragma endregion Getters

#pragma region Setters
    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        void SetFrequency(float frequency);

    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        void SetLacunarity(float lacunarity);

    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        void SetNoiseQuality(PerlinNoiseQuality noiseQuality);

    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        void SetOctaveCount(int32 octaveCount);

    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        void SetPersistence(int32 persistence);

    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        void SetSeed(int32 seed);
#pragma endregion Setters

    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        float GetValue(float x, float y, float z) const;

    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        float GetValueWithVector(FVector position) const;

    UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
        void CreateRandomSeed();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perlin Noise")
        bool generateRandomSeed;
};

