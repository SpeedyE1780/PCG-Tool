import { Spawn4DWFCLevel } from "../components/playcanvas/spawnWFCLevel";
import Viewer from "../components/playcanvas/viewer";
import GenerationParameters from "../components/levelGeneration/generationParameters";
import PCGMain from "../components/pcgMain";
import { PCGRequest } from "../components/pcgRequest";
import { useState } from "react";
import * as pc from "playcanvas";

let params = {};
let expansion = 0;

export default function WaveFunctionCollapse4DGeneration() {
  let [response, setResponse] = useState({});

  function updateResponse() {
    setResponse({
      json: response.json,
      minDimension: response.minDimension,
      maxDimension: response.maxDimension,
      currentDimension: response.currentDimension,
    });
  }

  function generateLevel() {
    const generationParameters = {
      nodeCount: params.count,
      nodeSize: params.size,
      startPosition: {
        x: params.xPosition,
        y: params.yPosition,
        z: params.zPosition,
      },
      axes: params.axis,
      expansionMode: expansion,
    };

    PCGRequest(
      "https://localhost:7060/levelgeneration/wavefunctioncollapsegeneration/generate4D",
      generationParameters,
      (json) => {
        response.json = json;
        response.minDimension = 0;
        response.maxDimension = 0;
        response.currentDimension = 0;
        Spawn4DWFCLevel(
          JSON.parse(json),
          generationParameters.nodeSize,
          response
        );
        updateResponse();
      }
    );
  }

  return (
    <PCGMain>
      <Viewer responseJSON={response.json}>
        <h1>4D Wave Function Collapse Generation</h1>
        <GenerationParameters config={params}></GenerationParameters>
        <label>Expansion Mode</label>
        <select onChange={(event) => (expansion = event.target.selectedIndex)}>
          <option value="BFS">Breadth First Search</option>
          <option value="DFS">Depth First Search</option>
        </select>
        <label>Dimension: {response.currentDimension}</label>
        <input
          type="range"
          min={response.minDimension}
          max={response.maxDimension}
          defaultValue="0"
          onChange={(event) => {
            response.currentDimension = event.target.valueAsNumber;
            updateResponse();
            pc.app.fire("SwitchDimension", response.currentDimension);
          }}
        ></input>
        <button onClick={generateLevel}>Generate</button>
      </Viewer>
    </PCGMain>
  );
}
