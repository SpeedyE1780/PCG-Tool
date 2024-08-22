import * as pc from "playcanvas";

const none = 0;
const left = 1;
const right = 2;
const forward = 4;
const backward = 8;

export default function SpawnMazeNode(walls) {
  let ground = new pc.Entity();
  ground.setLocalScale(5, 0.2, 5);
  ground.addComponent("model", {
    type: "box",
  });

  if ((walls & left) > 0) {
    let leftWall = new pc.Entity();
    leftWall.setLocalScale(0.1, 1, 5);
    leftWall.setPosition(-2.5, 0.5, 0);
    leftWall.addComponent("model", {
      type: "box",
    });
    pc.app.root.addChild(leftWall);
  }

  if ((walls & right) > 0) {
    let rightWall = new pc.Entity();
    rightWall.setLocalScale(0.1, 1, 5);
    rightWall.setPosition(2.5, 0.5, 0);
    rightWall.addComponent("model", {
      type: "box",
    });
    pc.app.root.addChild(rightWall);
  }

  if ((walls & forward) > 0) {
    let forwardWall = new pc.Entity();
    forwardWall.setLocalScale(5, 1, 0.1);
    forwardWall.setPosition(0, 0.5, -2.5);
    forwardWall.addComponent("model", {
      type: "box",
    });
    pc.app.root.addChild(forwardWall);
  }

  if ((walls & backward) > 0) {
    let backwardWall = new pc.Entity();
    backwardWall.setLocalScale(5, 1, 0.1);
    backwardWall.setPosition(0, 0.5, 2.5);
    backwardWall.addComponent("model", {
      type: "box",
    });
    pc.app.root.addChild(backwardWall);
  }

  pc.app.root.addChild(ground);
}
