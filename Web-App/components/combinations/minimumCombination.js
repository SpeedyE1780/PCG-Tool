import { useState } from "react";
import { getElementsFromElements } from "./common";

export default function MinimumCombination() {
  let [combinationInfo, setCombination] = useState("");
  let input = "";
  let minimum = 0;

  async function GenerateCombination() {
    let combinationElements = {
      elements: getElementsFromElements(input),
      minimumElements: minimum,
    };

    var request = {
      method: "POST",
      headers: {
        "content-type": "application/json",
      },
      body: JSON.stringify(combinationElements),
    };

    const result = await fetch(
      "https://localhost:7060/combination/generatewithminimumelement",
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
      <h2>Minimum Element Combination</h2>
      <input
        onChange={(event) => (input = event.target.value)}
        placeholder="Elements"
      ></input>
      <input
        onChange={(event) => (minimum = event.target.value)}
        placeholder="Minimum Element Count"
      ></input>
      <button onClick={GenerateCombination}>Generate</button>
      <h2>Combination: {combinationInfo}</h2>
    </div>
  );
}
