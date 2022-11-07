void ntuple2txt()
{
  TFile fInput("DUNE_TargetSim.root", "read");
  TTree* t = (TTree*)fInput.Get("DUNE_TargetSim");
  Double_t kineticEnergy;
  Double_t px, py, pz;
  Char_t particleName[32];
  Char_t procID[64];

  t->SetBranchAddress("kineticEnergy", &kineticEnergy);
  t->SetBranchAddress("px", &px);
  t->SetBranchAddress("py", &py);
  t->SetBranchAddress("pz", &pz);
  t->SetBranchAddress("particleName", particleName);
  t->SetBranchAddress("procID", procID);

  const ULong64_t nEntries = t->GetEntries();
  const Long64_t cntLimit = -1; // if cntLimit is negative, loop over all entries.
  ULong64_t cnt = 0;
  const ULong64_t cntUnit = ULong64_t(0.05*nEntries);

  ofstream fout;
  fout.open("dune_pi0.txt");

  for(ULong64_t i = 0; i < nEntries; i++)
  {
    if( i % (ULong64_t)cntUnit == 0 )
    {
      cout << "Scanning (" << i << "/" << nEntries << ", " << (Double_t)i/(Double_t)nEntries * 100. << "%)." << endl;
    }
    if( cnt >= cntLimit ) break;
    t->GetEntry(i);
    if( strcmp(particleName, "gamma") == 0 ) // -- 1
    {
      fout << px << " " << py << " " << pz << " " << kineticEnergy << " " << endl;
      cnt++;
    }
    else continue;
  }
  fInput.Close();
}
