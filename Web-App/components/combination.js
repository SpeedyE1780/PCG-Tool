import { useState } from "react";

function getElementsFromElements(input) {
  let elements = input.split(",");
  for (let i = 0; i < elements.length; ++i) {
    elements[i] = elements[i].trim();
  }

  return elements;
}

export default function Combination() {
  let [combinationInfo, setCombination] = useState("");
  let input = "";

  async function GenerateCombination() {
    let combinationElements = {
      elements: getElementsFromElements(input),
    };

    var request = {
      method: "POST",
      headers: {
        "content-type": "application/json",
      },
      body: JSON.stringify(combinationElements),
    };

    const result = await fetch(
      "https://localhost:7060/combination/generate",
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
      <h2>Normal Combination</h2>
      <input onChange={(event) => (input = event.target.value)}></input>
      <button onClick={GenerateCombination}>Generate</button>
      <h2>Combination: {combinationInfo}</h2>
    </div>
  );
}
