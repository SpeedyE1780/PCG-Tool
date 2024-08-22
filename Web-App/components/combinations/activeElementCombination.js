import { useState } from "react";
import { getElementsFromInput } from "./common";

export default function ActiveElementCombination() {
  let [combinationInfo, setCombination] = useState("");
  let input = "";
  let included = "";

  async function GenerateCombination() {
    let combinationElements = {
      elements: getElementsFromInput(input),
      included: getElementsFromInput(included),
    };

    var request = {
      method: "POST",
      headers: {
        "content-type": "application/json",
      },
      body: JSON.stringify(combinationElements),
    };

    const result = await fetch(
      "https://localhost:7060/combination/generatewithactiveelement",
      request
    );

    if (result.ok) {
      result
        .text()
        .then((body) => {
          combinationInfo = body;
          setCombination(combinationInfo);
        })
        .catch((err) => console.log(err));
    } else {
      alert("Error in result");
    }
  }

  return (
    <div>
      <h2>Active Element Combination</h2>
      <input
        onChange={(event) => (input = event.target.value)}
        placeholder="Elements"
      ></input>
      <input
        onChange={(event) => (included = event.target.value)}
        placeholder="Included Elements"
      ></input>
      <button onClick={GenerateCombination}>Generate</button>
      <h2>Combination: {combinationInfo}</h2>
    </div>
  );
}
