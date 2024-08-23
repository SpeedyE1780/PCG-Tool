import { SpawnLevel } from "../components/playcanvas/spawnLevel";
import Viewer from "../components/playcanvas/viewer";
import GenerationParameters from "../components/levelGeneration/generationParameters";
import PCGMain from "../components/pcgMain";
import { PCGRequest } from "../components/pcgRequest";
import { useState } from "react";

let params = {};

export default function SimpleGeneration() {
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
    };

    PCGRequest(
      "https://localhost:7060/levelgeneration/simplegeneration",
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
        <h1>Simple Generation</h1>
        <GenerationParameters config={params}></GenerationParameters>
        <button onClick={generateLevel}>Generate</button>
      </Viewer>
    </PCGMain>
  );
}
