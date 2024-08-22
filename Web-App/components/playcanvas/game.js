import { useEffect } from "react";
import * as pc from "playcanvas";
import CreateFlyCamera from "./flyCamera";

export default function Game() {
  function SpawnMazeNode(walls) {
    let ground = new pc.Entity();
    ground.setLocalScale(5, 0.2, 5);
    ground.addComponent("model", {
      type: "box",
    });

    let leftWall = new pc.Entity();
    leftWall.setLocalScale(0.1, 1, 5);
    leftWall.setPosition(-2.5, 0.5, 0);
    leftWall.addComponent("model", {
      type: "box",
    });

    let rightWall = new pc.Entity();
    rightWall.setLocalScale(0.1, 1, 5);
    rightWall.setPosition(2.5, 0.5, 0);
    rightWall.addComponent("model", {
      type: "box",
    });

    let forwardWall = new pc.Entity();
    forwardWall.setLocalScale(5, 1, 0.1);
    forwardWall.setPosition(0, 0.5, -2.5);
    forwardWall.addComponent("model", {
      type: "box",
    });

    let backwardWall = new pc.Entity();
    backwardWall.setLocalScale(5, 1, 0.1);
    backwardWall.setPosition(0, 0.5, 2.5);
    backwardWall.addComponent("model", {
      type: "box",
    });

    pc.app.root.addChild(ground);
    pc.app.root.addChild(leftWall);
    pc.app.root.addChild(rightWall);
    pc.app.root.addChild(forwardWall);
    pc.app.root.addChild(backwardWall);
  }

  useEffect(() => {
    // create a PlayCanvas application
    const canvas = document.getElementById("application");
    const app = new pc.Application(canvas, {
      mouse: new pc.Mouse(document.body),
      keyboard: new pc.Keyboard(window),
    });
    app.setCanvasResolution(pc.RESOLUTION_AUTO);
    app.setCanvasFillMode(pc.FILLMODE_FILL_WINDOW);
    app.start();

    CreateFlyCamera();

    // create a camera
    const camera = new pc.Entity();
    camera.addComponent("camera", {
      clearColor: new pc.Color(0.3, 0.3, 0.7),
    });
    camera.addComponent("script");
    camera.script.create("flyCamera");
    camera.setPosition(0, 5, 5);
    camera.lookAt(0, 0, 0);
    app.root.addChild(camera);

    // create a light
    const light = new pc.Entity();
    light.addComponent("light");
    light.setEulerAngles(45, 45, 0);
    app.root.addChild(light);

    SpawnMazeNode(0);
  }, []);

  return <canvas id="application"></canvas>;
}
