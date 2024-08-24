import { SpawnLevel } from "../components/playcanvas/spawnLevel";
import Viewer from "../components/playcanvas/viewer";
import GenerationParameters from "../components/levelGeneration/generationParameters";
import PCGMain from "../components/pcgMain";
import { PCGRequest } from "../components/pcgRequest";
import { useState } from "react";
import Vector3 from "../components/levelGeneration/vector3";

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
      offset: {
        x: params.xOffset,
        y: params.yOffset,
        z: params.zOffset,
      },
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
        <GenerationParameters
          hideAxis={true}
          config={params}
        ></GenerationParameters>
        <label>Node Offset</label>
        <Vector3
          onXChange={(event) => (params.xOffset = event.target.value)}
          onYChange={(event) => (params.yOffset = event.target.value)}
          onZChange={(event) => (params.zOffset = event.target.value)}
        ></Vector3>
        <button onClick={generateLevel}>Generate</button>
      </Viewer>
    </PCGMain>
  );
}
