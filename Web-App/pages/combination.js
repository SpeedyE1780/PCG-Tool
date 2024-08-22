import Combination from "../components/combinations/combination";
import MinimumCombination from "../components/combinations/minimumCombination";

export default function Home() {
  return (
    <div>
      <h1>Combination Generator</h1>
      <Combination></Combination>
      <MinimumCombination></MinimumCombination>
    </div>
  );
}
