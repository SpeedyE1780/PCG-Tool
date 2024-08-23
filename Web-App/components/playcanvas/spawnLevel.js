import * as pc from "playcanvas";

function SpawnLevelNode(position, nodeSize) {
  let node = new pc.Entity();
  node.setPosition(position);
  node.setLocalScale(nodeSize, nodeSize, nodeSize);
  node.addComponent("model", {
    type: "box",
  });
  node.addComponent("script");
  node.script.create("destroyNode");
  pc.app.root.addChild(node);
}

export function SpawnLevel(positions, nodeSize) {
  pc.app.fire("DestroyNode");

  positions.forEach((position) => {
    SpawnLevelNode(new pc.Vec3(position.x, position.y, position.z), nodeSize);
  });
}
