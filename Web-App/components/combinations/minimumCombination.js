import { useState } from "react";
import { getElementsFromInput } from "./common";
import { PCGRequest } from "../pcgRequest";

let input = "";
let minimum = 0;

export default function MinimumCombination() {
  let [combinationInfo, setCombination] = useState("");

  function GenerateCombination() {
    const combinationElements = {
      elements: getElementsFromInput(input),
      minimumElements: minimum,
    };

    PCGRequest(
      "https://localhost:7060/combination/generatewithminimumelement",
      combinationElements,
      (body) => setCombination(body)
    );
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
