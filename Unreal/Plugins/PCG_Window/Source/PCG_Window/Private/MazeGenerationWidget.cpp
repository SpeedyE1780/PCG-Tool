// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerationWidget.h"

void SMazeGenerationWidget::Construct(const FArguments& InArgs)
{
    ChildSlot
        [
            SNew(SBorder).Padding(FMargin(20))
                [
                    // Put your tab content here!
                    SNew(SVerticalBox)
                        + SVerticalBox::Slot().AutoHeight()
                        [
                            SNew(STextBlock)
                                .Text(FText::FromString("Generate Maze"))
                        ]
                        + SVerticalBox::Slot().AutoHeight()
                        [
                            SNew(SButton).OnClicked(this, &SMazeGenerationWidget::GenerateMaze)
                                [
                                    SNew(STextBlock).Text(FText::FromString("Generate Maze"))
                                ]
                        ]
                ]
        ];
}

FReply SMazeGenerationWidget::GenerateMaze()
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "GENERATE MAZE");
    return FReply::Handled();
}
