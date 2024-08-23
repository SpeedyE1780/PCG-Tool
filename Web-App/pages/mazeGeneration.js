import spawnMaze from "../components/playcanvas/spawnMaze";
import Viewer from "../components/playcanvas/viewer";
import GridConfiguration from "../components/levelGeneration/gridConfiguration";
import PCGMain from "../components/pcgMain";
import { useState } from "react";
import { PCGRequest } from "../components/pcgRequest";

let gridConfig = {};
let selectedAlgorithm = 0;

export default function MazeGeneration() {
  let [generatedJSON, setGeneratedJSON] = useState("");

  function generateMaze() {
    const mazeParameters = {
      width: gridConfig.width,
      height: gridConfig.height,
      algorithm: selectedAlgorithm,
    };

    PCGRequest(
      "https://localhost:7060/maze/generate",
      mazeParameters,
      (body) => {
        setGeneratedJSON(body);
        spawnMaze(JSON.parse(body));
      }
    );
  }

  return (
    <PCGMain>
      <Viewer responseJSON={generatedJSON}>
        <h1>Maze Generation</h1>
        <GridConfiguration config={gridConfig}></GridConfiguration>
        <labe>Maze Algorithm</labe>
        <select
          onChange={(event) => (selectedAlgorithm = event.target.selectedIndex)}
        >
          <option value="aldousBroder">Aldous Broder</option>
          <option value="binaryTreeNE">Binary Tree NE</option>
          <option value="binaryTreeNW">Binary Tree NW</option>
          <option value="binaryTreeSE">Binary Tree SE</option>
          <option value="binaryTreeSW">Binary Tree SW</option>
          <option value="blobbyDivisionCorridors">
            Blobby Division Corridors
          </option>
          <option value="blobbyDivisionSmall">Blobby Division Small</option>
          <option value="blobbyDivisionMedium">Blobby Division Medium</option>
          <option value="blobbyDivisionLarge">Blobby Division Large</option>
          <option value="blobbyDivisionHuge">Blobby Division Huge</option>
          <option value="eller">Eller</option>
          <option value="growingTreeOldest">Growing Tree Oldest</option>
          <option value="growingTreeMiddle">Growing Tree Middle</option>
          <option value="growingTreeNewest">Growing Tree Newest</option>
          <option value="growingTreeRandom">Growing Tree Random</option>
          <option value="huntAndKill">Hunt And Kill</option>
          <option value="kruskal">Kruskal</option>
          <option value="prim">Prim</option>
          <option value="recursiveBacktracker">Recursive Backtracker</option>
          <option value="recursiveDivision">Recursive Division</option>
          <option value="sidewinder">Sidewinder</option>
          <option value="wilson">Wilson</option>
        </select>
        <button onClick={generateMaze}>Generate Maze</button>
      </Viewer>
    </PCGMain>
  );
}
