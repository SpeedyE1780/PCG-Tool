import { SpawnLevel } from "../components/playcanvas/spawnLevel";
import Viewer from "../components/playcanvas/viewer";
import GenerationParameters from "../components/levelGeneration/generationParameters";
import PCGMain from "../components/pcgMain";
import { useState } from "react";
import { PCGRequest } from "../components/pcgRequest";

let params = {};
let disable = false;

export default function MultiDimensionGeneration() {
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
      disableOverlap: disable,
    };

    PCGRequest(
      "https://localhost:7060/levelgeneration/multidimensiongeneration",
      generationParameters,
      (body) => {
        setGeneratedJSON(body);
        SpawnLevel(JSON.parse(body), generationParameters.nodeSize);
      }
    );
  }

  return (
    <PCGMain>
      <Viewer responseJSON={generatedJSON}>
        <h1>Multi Dimension Generation</h1>
        <GenerationParameters config={params}></GenerationParameters>
        <input
          type="checkbox"
          onChange={(event) => (disable = event.target.checked)}
        ></input>
        <label>Disable Overlap</label>
        <button onClick={generateLevel}>Generate</button>
      </Viewer>
    </PCGMain>
  );
}
