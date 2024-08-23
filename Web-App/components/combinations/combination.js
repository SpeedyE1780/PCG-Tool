import { useState } from "react";
import { getElementsFromInput } from "./common";
import { PCGRequest } from "../pcgRequest";

let input = "";

export default function Combination() {
  let [combinationInfo, setCombination] = useState("");

  function GenerateCombination() {
    const combinationElements = {
      elements: getElementsFromInput(input),
    };

    PCGRequest(
      "https://localhost:7060/combination/generate",
      combinationElements,
      (body) => setCombination(body)
    );
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
