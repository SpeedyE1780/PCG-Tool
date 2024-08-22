import * as pc from "playcanvas";

const left = 1;
const right = 2;
const forward = 4;
const backward = 8;

export default function SpawnMazeNode(x, y, adjacentNodes) {
  const position = new pc.Vec3(x * 5, 0, y * 5);
  let ground = new pc.Entity();
  ground.setPosition(position);
  ground.setLocalScale(5, 0.2, 5);
  ground.addComponent("model", {
    type: "box",
  });
  ground.addComponent("script");
  ground.script.create("destroyNode");
  pc.app.root.addChild(ground);

  if ((adjacentNodes & left) == 0) {
    let leftWall = new pc.Entity();
    leftWall.setLocalScale(0.1, 1, 5);
    leftWall.setPosition(position.x + -2.5, position.y + 0.5, position.z + 0);
    leftWall.addComponent("model", {
      type: "box",
    });
    leftWall.addComponent("script");
    leftWall.script.create("destroyNode");
    pc.app.root.addChild(leftWall);
  }

  if ((adjacentNodes & right) == 0) {
    let rightWall = new pc.Entity();
    rightWall.setLocalScale(0.1, 1, 5);
    rightWall.setPosition(position.x + 2.5, position.y + 0.5, position.z + 0);
    rightWall.addComponent("model", {
      type: "box",
    });
    rightWall.addComponent("script");
    rightWall.script.create("destroyNode");
    pc.app.root.addChild(rightWall);
  }

  if ((adjacentNodes & forward) == 0) {
    let forwardWall = new pc.Entity();
    forwardWall.setLocalScale(5, 1, 0.1);
    forwardWall.setPosition(
      position.x + 0,
      position.y + 0.5,
      position.z + 2.5
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
    backwardWall.setLocalScale(5, 1, 0.1);
    backwardWall.setPosition(
      position.x + 0,
      position.y + 0.5,
      position.z + -2.5
    );
    backwardWall.addComponent("model", {
      type: "box",
    });
    backwardWall.addComponent("script");
    backwardWall.script.create("destroyNode");
    pc.app.root.addChild(backwardWall);
  }
}
