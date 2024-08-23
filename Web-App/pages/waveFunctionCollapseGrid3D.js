import * as pc from "playcanvas";
import { SpawnWFCGrid3D } from "../components/playcanvas/spawnLevelNode";
import Viewer from "../components/playcanvas/viewer";
import GridConfiguration from "../components/levelGeneration/gridConfiguration";
import PCGMain from "../components/pcgMain";

export default function waveFunctionCollapseGrid3D() {
  let gridConfig = {};

  async function generateGrid() {
    let gridParameters = {
      width: gridConfig.width,
      height: gridConfig.height,
      depth: gridConfig.depth,
    };

    console.log(gridParameters);

    pc.app.fire("DestroyNode");

    var request = {
      method: "POST",
      headers: {
        "content-type": "application/json",
      },
      body: JSON.stringify(gridParameters),
    };

    const result = await fetch(
      "https://localhost:7060/levelgeneration/wavefunctioncollapsegeneration/grid3d",
      request
    );

    if (result.ok) {
      result
        .json()
        .then((body) => {
          console.log(body);
          SpawnWFCGrid3D(body);
        })
        .catch((err) => console.log(err));
    } else {
      alert("Error in result");
    }
  }

  return (
    <PCGMain>
      <Viewer>
        <h1>Wave Function Collapse Grid 3D Generation</h1>
        <GridConfiguration config={gridConfig} is3D={true}></GridConfiguration>
        <button onClick={generateGrid}>Generate</button>
      </Viewer>
    </PCGMain>
  );
}
