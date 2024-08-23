import * as pc from "playcanvas";
import { Planes, SpawnWFCGrid } from "../components/playcanvas/spawnLevelNode";
import Viewer from "../components/playcanvas/viewer";
import GridConfiguration from "../components/levelGeneration/gridConfiguration";

export default function waveFunctionCollapseGrid2D() {
  let gridConfig = {};
  let gridPlane = Planes[0];

  async function generateGrid() {
    let gridParameters = {
      width: gridConfig.width,
      height: gridConfig.height,
      plane: gridPlane,
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
      "https://localhost:7060/levelgeneration/wavefunctioncollapsegeneration/grid2d",
      request
    );

    if (result.ok) {
      result
        .json()
        .then((body) => {
          console.log(body);
          SpawnWFCGrid(body, gridPlane);
        })
        .catch((err) => console.log(err));
    } else {
      alert("Error in result");
    }
  }

  return (
    <Viewer>
      <h1>Wave Function Collapse Grid 2D Generation</h1>
      <GridConfiguration config={gridConfig}></GridConfiguration>
      <select
        onChange={(event) => {
          gridPlane = Planes[event.target.selectedIndex];
        }}
      >
        <option value="XY">XY</option>
        <option value="XZ">XZ</option>
        <option value="YZ">YZ</option>
      </select>
      <button onClick={generateGrid}>Generate</button>
    </Viewer>
  );
}
