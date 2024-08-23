import * as pc from "playcanvas";
import { SpawnLevel } from "../components/playcanvas/spawnLevelNode";
import Viewer from "../components/playcanvas/viewer";
import GenerationParameters from "../components/levelGeneration/generationParameters";
import PCGMain from "../components/pcgMain";

export default function SimpleGeneration() {
  let params = {};

  async function generateLevel() {
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
    console.log(generationParameters);

    pc.app.fire("DestroyNode");

    var request = {
      method: "POST",
      headers: {
        "content-type": "application/json",
      },
      body: JSON.stringify(generationParameters),
    };

    const result = await fetch(
      "https://localhost:7060/levelgeneration/simplegeneration",
      request
    );

    if (result.ok) {
      result
        .json()
        .then((body) => {
          console.log(body);
          SpawnLevel(body, generationParameters.nodeSize);
        })
        .catch((err) => console.log(err));
    } else {
      alert("Error in result");
    }
  }

  return (
    <PCGMain>
      <Viewer>
        <h1>Simple Generation</h1>
        <GenerationParameters config={params}></GenerationParameters>
        <button onClick={generateLevel}>Generate</button>
      </Viewer>
    </PCGMain>
  );
}
