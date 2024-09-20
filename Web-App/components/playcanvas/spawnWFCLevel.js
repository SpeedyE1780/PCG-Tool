import * as pc from "playcanvas";
import GetColor from "./materials";

const left = 1;
const right = 2;
const forward = 4;
const backward = 8;
const up = 16;
const down = 32;
const portalIn = 64;
const portalOut = 128;
const XY = 15;
const XZ = 51;
const YZ = 60;
export const Planes = [XY, XZ, YZ];

function spawnWFCEntity(position, scale) {
  let entity = new pc.Entity();
  entity.setPosition(position);
  entity.setLocalScale(scale);
  entity.addComponent("model", {
    type: "box",
  });
  entity.addComponent("script");
  entity.script.create("destroyNode");
  pc.app.root.addChild(entity);

  return entity;
}

function SpawnWFCNode(position, adjacentNodes, size) {
  const groundScale = new pc.Vec3(size, size * 0.04, size);
  spawnWFCEntity(position, groundScale);

  if ((adjacentNodes & left) == 0) {
    const wallPosition = new pc.Vec3(
      position.x - size * 0.5,
      position.y + size * 0.1,
      position.z
    );
    const scale = new pc.Vec3(size * 0.02, size * 0.2, size);
    spawnWFCEntity(wallPosition, scale);
  }

  if ((adjacentNodes & right) == 0) {
    const wallPosition = new pc.Vec3(
      position.x + size * 0.5,
      position.y + size * 0.1,
      position.z
    );
    const scale = new pc.Vec3(size * 0.02, size * 0.2, size);
    spawnWFCEntity(wallPosition, scale);
  }

  if ((adjacentNodes & forward) == 0) {
    const wallPosition = new pc.Vec3(
      position.x,
      position.y + size * 0.1,
      position.z + size * 0.5
    );
    const scale = new pc.Vec3(size, size * 0.2, size * 0.02);
    spawnWFCEntity(wallPosition, scale);
  }

  if ((adjacentNodes & backward) == 0) {
    const wallPosition = new pc.Vec3(
      position.x,
      position.y + size * 0.1,
      position.z - size * 0.5
    );
    const scale = new pc.Vec3(size, size * 0.2, size * 0.02);
    spawnWFCEntity(wallPosition, scale);
  }

  if ((adjacentNodes & up) != 0) {
    const wallPosition = new pc.Vec3(
      position.x,
      position.y + size * 0.25,
      position.z
    );
    const scale = new pc.Vec3(size * 0.2, size * 0.5, size * 0.2);
    spawnWFCEntity(wallPosition, scale);
  }

  if ((adjacentNodes & down) != 0) {
    const wallPosition = new pc.Vec3(
      position.x,
      position.y - size * 0.25,
      position.z
    );
    const scale = new pc.Vec3(size * 0.2, size * 0.5, size * 0.2);
    spawnWFCEntity(wallPosition, scale);
  }
}

function updateMeshMaterial(mesh, dimension) {
  var material = mesh.material.clone();
  material.diffuse = GetColor(dimension);
  material.update();
  mesh.material = material;
}

function spawn4dWFCEntity(position, scale, dimension) {
  let entity = spawnWFCEntity(position, scale);
  entity.script.create("dimensionNode");
  entity.script.dimensionNode.dimension = dimension;
  pc.app.root.addChild(entity);
  return entity;
}

function spawnWFCPortal(position, scale, dimension) {
  let entity = new pc.Entity();
  entity.setPosition(position);
  entity.setLocalScale(scale);
  entity.addComponent("model", {
    type: "cone",
  });
  entity.addComponent("script");
  entity.script.create("destroyNode");
  pc.app.root.addChild(entity);

  entity.script.create("dimensionNode");
  entity.script.dimensionNode.dimension = dimension;
  pc.app.root.addChild(entity);

  return entity;
}

function Spawn4DWFCNode(position, adjacentNodes, size, dimension) {
  const groundScale = new pc.Vec3(size, size * 0.04, size);
  let ground = spawn4dWFCEntity(position, groundScale, dimension);
  ground.model.meshInstances.forEach((mesh) =>
    updateMeshMaterial(mesh, dimension)
  );

  if ((adjacentNodes & left) == 0) {
    const wallPosition = new pc.Vec3(
      position.x - size * 0.5,
      position.y + size * 0.1,
      position.z
    );
    const scale = new pc.Vec3(size * 0.02, size * 0.2, size);
    spawn4dWFCEntity(wallPosition, scale, dimension);
  }

  if ((adjacentNodes & right) == 0) {
    const wallPosition = new pc.Vec3(
      position.x + size * 0.5,
      position.y + size * 0.1,
      position.z
    );
    const scale = new pc.Vec3(size * 0.02, size * 0.2, size);
    spawn4dWFCEntity(wallPosition, scale, dimension);
  }

  if ((adjacentNodes & forward) == 0) {
    const wallPosition = new pc.Vec3(
      position.x,
      position.y + size * 0.1,
      position.z + size * 0.5
    );
    const scale = new pc.Vec3(size, size * 0.2, size * 0.02);
    spawn4dWFCEntity(wallPosition, scale, dimension);
  }

  if ((adjacentNodes & backward) == 0) {
    const wallPosition = new pc.Vec3(
      position.x,
      position.y + size * 0.1,
      position.z - size * 0.5
    );
    const scale = new pc.Vec3(size, size * 0.2, size * 0.02);
    spawn4dWFCEntity(wallPosition, scale, dimension);
  }

  if ((adjacentNodes & up) != 0) {
    const wallPosition = new pc.Vec3(
      position.x,
      position.y + size * 0.25,
      position.z
    );
    const scale = new pc.Vec3(size * 0.2, size * 0.5, size * 0.2);
    spawn4dWFCEntity(wallPosition, scale, dimension);
  }

  if ((adjacentNodes & down) != 0) {
    const wallPosition = new pc.Vec3(
      position.x,
      position.y - size * 0.25,
      position.z
    );
    const scale = new pc.Vec3(size * 0.2, size * 0.5, size * 0.2);
    spawn4dWFCEntity(wallPosition, scale, dimension);
  }

  if ((adjacentNodes & portalIn) != 0) {
    const scale = new pc.Vec3(size * 0.2, size * 0.2, size * 0.2);
    const portalPosition = new pc.Vec3(
      position.x + size * 0.25,
      position.y + size * 0.1,
      position.z
    );

    let portalIn = spawnWFCPortal(portalPosition, scale, dimension);
    portalIn.model.meshInstances.forEach((mesh) =>
      updateMeshMaterial(mesh, dimension + 1)
    );
  }

  if ((adjacentNodes & portalOut) != 0) {
    const scale = new pc.Vec3(size * 0.2, size * 0.2, size * 0.2);
    const portalPosition = new pc.Vec3(
      position.x - size * 0.25,
      position.y + size * 0.1,
      position.z
    );

    let portalOut = spawnWFCPortal(portalPosition, scale, dimension);
    portalOut.model.meshInstances.forEach((mesh) =>
      updateMeshMaterial(mesh, dimension - 1)
    );
    portalOut.setLocalEulerAngles(180, 0, 0);
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

export function Spawn4DWFCLevel(wfcNodes, size, response) {
  pc.app.fire("DestroyNode");

  wfcNodes.forEach((node) => {
    const position = new pc.Vec3(
      node.position.x,
      node.position.y,
      node.position.z
    );
    response.minDimension = Math.min(node.position.w, response.minDimension);
    response.maxDimension = Math.max(node.position.w, response.maxDimension);
    Spawn4DWFCNode(position, node.direction, size, node.position.w);
  });

  pc.app.fire("SwitchDimension", 0);
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
