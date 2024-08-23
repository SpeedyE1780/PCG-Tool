import styles from "../../styles/Home.module.css";

function getIndexFromInput(input) {
  let indices = input.split(",");
  for (let i = 0; i < indices.length; ++i) {
    indices[i] = Number(indices[i].trim());
  }

  return indices;
}

export default function NodeList(props) {
  return (
    <div className={styles.nodesList}>
      {props.nodes.map((element, i) => (
        <div key={i} className={styles.nodesList}>
          <label>Node: {i}</label>
          <div>
            <label>Node Name:</label>
            <input
              onChange={(event) => {
                props.nodes[i].name = event.target.value;
              }}
            ></input>
          </div>
          <div>
            <label>Next Node Index:</label>
            <input
              onChange={(event) => {
                props.nodes[i].nextNodes = getIndexFromInput(event.target.value);
              }}
            ></input>
          </div>
        </div>
      ))}
    </div>
  );
}
