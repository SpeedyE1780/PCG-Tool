import SpawnMazeNode from "../maze/spawnMazeNode";

export default function spawnMaze(mazeNodes) {
  mazeNodes.forEach((element) => {
    SpawnMazeNode(element.x, element.y, element.adjacentNodes);
  });
}
