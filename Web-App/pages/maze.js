import * as pc from "playcanvas";
import spawnMaze from "../components/playcanvas/spawnMaze";
import Viewer from "../components/playcanvas/viewer";

export default function Maze() {
  let Width = 0;
  let Height = 0;
  let selectedAlgorithm = 0;

  async function generateMaze() {
    const mazeParameters = {
      width: Width,
      height: Height,
      algorithm: selectedAlgorithm,
    };

    pc.app.fire("DestroyNode");

    var request = {
      method: "POST",
      headers: {
        "content-type": "application/json",
      },
      body: JSON.stringify(mazeParameters),
    };

    const result = await fetch("https://localhost:7060/maze/generate", request);

    if (result.ok) {
      result
        .json()
        .then((body) => {
          console.log(body);
          spawnMaze(body);
        })
        .catch((err) => console.log(err));
    } else {
      alert("Error in result");
    }
  }

  return (
    <Viewer>
      <h1>Maze Generation</h1>
      <input
        placeholder="Width"
        onChange={(event) => (Width = event.target.value)}
      ></input>
      <input
        placeholder="Height"
        onChange={(event) => (Height = event.target.value)}
      ></input>
      <select
        onChange={(event) => (selectedAlgorithm = event.target.selectedIndex)}
      >
        <option value="aldousBroder">Aldous Broder</option>
        <option value="wilson">Wilson</option>
        <option value="binaryTreeNE">Binary Tree NE</option>
        <option value="binaryTreeNW">Binary Tree NW</option>
        <option value="binaryTreeSE">Binary Tree SE</option>
        <option value="binaryTreeSW">Binary Tree SW</option>
        <option value="sidewinder">Sidewinder</option>
        <option value="eller">Eller</option>
        <option value="huntAndKill">Hunt And Kill</option>
        <option value="recursiveBacktracker">Recursive Backtracker</option>
        <option value="recursiveDivision">Recursive Division</option>
        <option value="kruskal">Kruskal</option>
        <option value="prim">Prim</option>
        <option value="growingTreeOldest">Growing Tree Oldest</option>
        <option value="growingTreeMiddle">Growing Tree Middle</option>
        <option value="growingTreeNewest">Growing Tree Newest</option>
        <option value="growingTreeRandom">Growing Tree Random</option>
        <option value="blobbyDivisionCorridors">
          Blobby Division Corridors
        </option>
        <option value="blobbyDivisionSmall">Blobby Division Small</option>
        <option value="blobbyDivisionMedium">Blobby Division Medium</option>
        <option value="blobbyDivisionLarge">Blobby Division Large</option>
        <option value="blobbyDivisionHuge">Blobby Division Huge</option>
      </select>
      <button onClick={generateMaze}>Generate</button>
    </Viewer>
  );
}
