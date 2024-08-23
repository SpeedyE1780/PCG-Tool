import * as pc from "playcanvas";

const left = 1;
const right = 2;
const forward = 4;
const backward = 8;
const up = 16;
const down = 32;
const XY = 15;
const XZ = 51;
const YZ = 60;
export const Planes = [XY, XZ, YZ];

function SpawnWFCNode(position, adjacentNodes, size) {
  let ground = new pc.Entity();
  ground.setPosition(position);
  ground.setLocalScale(size, size * 0.04, size);
  ground.addComponent("model", {
    type: "box",
  });
  ground.addComponent("script");
  ground.script.create("destroyNode");
  pc.app.root.addChild(ground);

  if ((adjacentNodes & left) == 0) {
    let leftWall = new pc.Entity();
    leftWall.setLocalScale(size * 0.02, size * 0.2, size);
    leftWall.setPosition(
      position.x - size * 0.5,
      position.y + size * 0.1,
      position.z
    );
    leftWall.addComponent("model", {
      type: "box",
    });
    leftWall.addComponent("script");
    leftWall.script.create("destroyNode");
    pc.app.root.addChild(leftWall);
  }

  if ((adjacentNodes & right) == 0) {
    let rightWall = new pc.Entity();
    rightWall.setLocalScale(size * 0.02, size * 0.2, size);
    rightWall.setPosition(
      position.x + size * 0.5,
      position.y + size * 0.1,
      position.z
    );
    rightWall.addComponent("model", {
      type: "box",
    });
    rightWall.addComponent("script");
    rightWall.script.create("destroyNode");
    pc.app.root.addChild(rightWall);
  }

  if ((adjacentNodes & forward) == 0) {
    let forwardWall = new pc.Entity();
    forwardWall.setLocalScale(size, size * 0.2, size * 0.02);
    forwardWall.setPosition(
      position.x,
      position.y + size * 0.1,
      position.z + size * 0.5
    );
    forwardWall.addComponent("model", {
      type: "box",
    });
    forwardWall.addComponent("script");
    forwardWall.script.create("destroyNode");
    pc.app.root.addChild(forwardWall);
  }

  if ((adjacentNodes & backward) == 0) {
    let backwardWall = new pc.Entity();
    backwardWall.setLocalScale(size, size * 0.2, size * 0.02);
    backwardWall.setPosition(
      position.x,
      position.y + size * 0.1,
      position.z - size * 0.5
    );
    backwardWall.addComponent("model", {
      type: "box",
    });
    backwardWall.addComponent("script");
    backwardWall.script.create("destroyNode");
    pc.app.root.addChild(backwardWall);
  }

  if ((adjacentNodes & up) != 0) {
    let upConnection = new pc.Entity();
    upConnection.setLocalScale(size * 0.2, size * 0.5, size * 0.2);
    upConnection.setPosition(position.x, position.y + size * 0.25, position.z);
    upConnection.addComponent("model", {
      type: "box",
    });
    upConnection.addComponent("script");
    upConnection.script.create("destroyNode");
    pc.app.root.addChild(upConnection);
  }

  if ((adjacentNodes & down) != 0) {
    let downConnection = new pc.Entity();
    downConnection.setLocalScale(size * 0.2, size * 0.5, size * 0.2);
    downConnection.setPosition(
      position.x,
      position.y - size * 0.25,
      position.z
    );
    downConnection.addComponent("model", {
      type: "box",
    });
    downConnection.addComponent("script");
    downConnection.script.create("destroyNode");
    pc.app.root.addChild(downConnection);
  }
}

export function SpawnWFCLevel(wfcNodes, size) {
  pc.app.fire("DestroyNode");

  wfcNodes.forEach((node) => {
    const position = new pc.Vec3(
      node.position.x,
      node.position.y,
      node.position.z
    );
    SpawnWFCNode(position, node.direction, size);
  });
}

export function SpawnWFCGrid(wfcNodes, plane) {
  function getNodePosition(x, y) {
    switch (plane) {
      case XY: {
        return new pc.Vec3(x, y, 0);
      }
      case XZ: {
        return new pc.Vec3(x, 0, y);
      }
      case YZ: {
        return new pc.Vec3(0, x, y);
      }
    }
  }

  pc.app.fire("DestroyNode");
  wfcNodes.forEach((node) => {
    const position = getNodePosition(node.x, node.y);
    SpawnWFCNode(position, node.adjacentNodes, 1);
  });
}

export function SpawnWFCGrid3D(wfcNodes) {
  pc.app.fire("DestroyNode");
  wfcNodes.forEach((node) => {
    const position = new pc.Vec3(node.x, node.y, node.z);
    SpawnWFCNode(position, node.adjacentNodes, 1);
  });
}
