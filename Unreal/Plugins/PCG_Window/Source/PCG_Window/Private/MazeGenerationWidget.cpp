// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerationWidget.h"

#define LOCTEXT_NAMESPACE "SMazeGenerationWidget"

const TArray<FText> SMazeGenerationWidget::Algorithms =
{
    LOCTEXT("aldousBroder", "Aldous Broder"),
    LOCTEXT("wilson", "Wilson"),
    LOCTEXT("binaryTreeNE", "Binary Tree NE"),
    LOCTEXT("binaryTreeNW", "Binary Tree NW"),
    LOCTEXT("binaryTreeSE", "Binary Tree SE"),
    LOCTEXT("binaryTreeSW", "Binary Tree SW"),
    LOCTEXT("sidewinder", "Sidewinder"),
};

void SMazeGenerationWidget::Construct(const FArguments& InArgs)
{
    SelectedAlgorithm = MakeShareable(new FText(Algorithms[0]));

    for (const auto& Algorithm : Algorithms)
    {
        AlgorithmsOptions.Add(MakeShareable(new FText(Algorithm)));
    }

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
                            SNew(SComboBox<TSharedPtr<FText>>)
                                .InitiallySelectedItem(SelectedAlgorithm)
                                .OptionsSource(&AlgorithmsOptions)
                                .OnSelectionChanged_Lambda([this](TSharedPtr<FText> NewSelection, ESelectInfo::Type SelectInfo)
                                    {
                                        if (NewSelection == nullptr)
                                        {
                                            return;
                                        }

                                        if (SelectInfo == ESelectInfo::Type::OnMouseClick)
                                        {
                                            SelectedAlgorithm = NewSelection;
                                        }
                                    })
                                .OnGenerateWidget_Lambda([this](TSharedPtr<FText> Value)
                                    {
                                        return SNew(STextBlock)
                                            .Text(*Value);
                                    })
                                [
                                    SNew(STextBlock)
                                        .Font(FCoreStyle::GetDefaultFontStyle("Regular", 18))
                                        .Text_Lambda([this]()
                                            {
                                                return SelectedAlgorithm.IsValid() ? *SelectedAlgorithm : FText::GetEmpty();
                                            })
                                ]
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
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, SelectedAlgorithm->ToString());
    return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
