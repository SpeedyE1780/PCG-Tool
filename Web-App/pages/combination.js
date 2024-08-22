import { useState } from "react";

export default function Home() {
  let [combinationInfo, setCombination] = useState("");
  let input = "";

  async function GenerateCombination() {
    let combinationElements = {
      elements: input.split(","),
    };

    combinationElements.elements.forEach((element, index, array) =>
      element.trim()
    );
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
      <h1>Combination Generator</h1>
      <input onChange={(event) => (input = event.target.value)}></input>
      <button onClick={GenerateCombination}>Generate</button>
      <h2>Combination: {combinationInfo}</h2>
    </div>
  );
}
