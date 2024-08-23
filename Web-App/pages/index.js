import Head from "next/head";
import styles from "../styles/Home.module.css";
import PCGHeader from "../components/pcgHeader";
import Link from "next/link";

export default function Home() {
  return (
    <div>
      <PCGHeader></PCGHeader>
      <main>
        <h1 className={styles.title}>Welcome to PCG Web APP!</h1>
        <ul>
          <li>
            <Link href="combinationGeneration">
              <h3>Combination Generation</h3>
            </Link>
          </li>
          <li>
            <Link href="cyclicSequenceGeneration">
              <h3>Cyclic Sequence Generation</h3>
            </Link>
          </li>
          <li>
            <Link href="mazeGeneration">
              <h3>Maze Generation</h3>
            </Link>
          </li>
          <li>
            <Link href="sequenceGeneration">
              <h3>Sequence Generation</h3>
            </Link>
          </li>
          <li>
            <Link href="simpleGeneration">
              <h3>Simple Generation</h3>
            </Link>
          </li>
          <li>
            <Link href="multiDimensionGeneration">
              <h3>Multi Dimension Generation</h3>
            </Link>
          </li>
          <li>
            <Link href="waveFunctionCollapseGeneration">
              <h3>Wave Function Collapse Generation</h3>
            </Link>
          </li>
          <li>
            <Link href="waveFunctionCollapseGrid2DGeneration">
              <h3>Wave Function Collapse Grid 2D Generation</h3>
            </Link>
          </li>
          <li>
            <Link href="waveFunctionCollapseGrid3DGeneration">
              <h3>Wave Function Collapse Grid 3D Generation</h3>
            </Link>
          </li>
        </ul>
      </main>

      <footer>
        <a
          href="https://vercel.com?utm_source=create-next-app&utm_medium=default-template&utm_campaign=create-next-app"
          target="_blank"
          rel="noopener noreferrer"
        >
          Powered by{" "}
          <img src="/vercel.svg" alt="Vercel" className={styles.logo} />
        </a>
      </footer>

      <style jsx>{`
        main {
          padding: 5rem 0;
          flex: 1;
          display: flex;
          flex-direction: column;
          justify-content: center;
          align-items: center;
        }
        footer {
          width: 100%;
          height: 100px;
          border-top: 1px solid #eaeaea;
          display: flex;
          justify-content: center;
          align-items: center;
        }
        footer img {
          margin-left: 0.5rem;
        }
        footer a {
          display: flex;
          justify-content: center;
          align-items: center;
          text-decoration: none;
          color: inherit;
        }
        code {
          background: #fafafa;
          border-radius: 5px;
          padding: 0.75rem;
          font-size: 1.1rem;
          font-family: Menlo, Monaco, Lucida Console, Liberation Mono,
            DejaVu Sans Mono, Bitstream Vera Sans Mono, Courier New, monospace;
        }
      `}</style>

      <style jsx global>{`
        html,
        body {
          padding: 0;
          margin: 0;
          font-family: -apple-system, BlinkMacSystemFont, Segoe UI, Roboto,
            Oxygen, Ubuntu, Cantarell, Fira Sans, Droid Sans, Helvetica Neue,
            sans-serif;
        }
        * {
          box-sizing: border-box;
        }
      `}</style>
    </div>
  );
}
