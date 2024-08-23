import { SpawnWFCLevel } from "../components/playcanvas/spawnWFCLevel";
import Viewer from "../components/playcanvas/viewer";
import GenerationParameters from "../components/levelGeneration/generationParameters";
import PCGMain from "../components/pcgMain";
import { PCGRequest } from "../components/pcgRequest";
import { useState } from "react";

let params = {};
let expansion = 0;

export default function WaveFunctionCollapseGeneration() {
  let [generatedJSON, setGeneratedJSON] = useState("");

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
      "https://localhost:7060/levelgeneration/wavefunctioncollapsegeneration/generate",
      generationParameters,
      (json) => {
        setGeneratedJSON(json);
        SpawnWFCLevel(JSON.parse(json), generationParameters.nodeSize);
      }
    );
  }

  return (
    <PCGMain>
      <Viewer responseJSON={generatedJSON}>
        <h1>Wave Function Collapse Generation</h1>
        <GenerationParameters config={params}></GenerationParameters>
        <label>Expansion Mode</label>
        <select onChange={(event) => (expansion = event.target.selectedIndex)}>
          <option value="BFS">Breadth First Search</option>
          <option value="DFS">Depth First Search</option>
        </select>
        <button onClick={generateLevel}>Generate</button>
      </Viewer>
    </PCGMain>
  );
}
