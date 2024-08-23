import { useState } from "react";
import { getElementsFromInput } from "./common";
import { PCGRequest } from "../pcgRequest";

let input = "";
let included = "";

export default function ActiveElementCombination() {
  let [combinationInfo, setCombination] = useState("");

  function GenerateCombination() {
    const combinationElements = {
      elements: getElementsFromInput(input),
      included: getElementsFromInput(included),
    };

    PCGRequest(
      "https://localhost:7060/combination/generatewithactiveelement",
      combinationElements,
      (body) => setCombination(body)
    );
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
