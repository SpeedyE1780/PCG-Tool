import * as pc from "playcanvas";
import { SpawnLevel } from "../components/playcanvas/spawnLevelNode";
import Viewer from "../components/playcanvas/viewer";
import GenerationParameters from "../components/levelGeneration/generationParameters";

export default function MultiDimensionGeneration() {
  let params = {};
  let disable = false;

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
      disableOverlap: disable,
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
      "https://localhost:7060/levelgeneration/multidimensiongeneration",
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
    <Viewer>
      <h1>Multi Dimension Generation</h1>
      <GenerationParameters config={params}></GenerationParameters>
      <input
        type="checkbox"
        onChange={(event) => (disable = event.target.checked)}
      ></input>
      <label>Disable Overlap</label>
      <button onClick={generateLevel}>Generate</button>
    </Viewer>
  );
}
