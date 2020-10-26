/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once
class CTrainTrackManager;

struct STrackNode
{
    CVector position;
    float   railDistance;

    STrackNode(std::int16_t x, std::int16_t y, std::int16_t z, std::uint16_t distance)
    {
        position.fX = 8.0f * x;
        position.fY = 8.0f * y;
        position.fZ = 8.0f * z;
        railDistance = 3.0f * distance;            // TODO(Jusonex, feature/custom-train-tracks/9063a3dc080): Remove distance
    }

    STrackNode(const CVector& pos) : position(pos) {}
    STrackNode() {}
};

class CTrainTrack : public CElement
{
public:
    CTrainTrack(CTrainTrackManager* pManager, const std::vector<STrackNode>& nodes, bool linkLastNodes, CElement* pParent, uchar defaultTrackId = 0xFF);
    // TODO: Add move constructor
    virtual ~CTrainTrack();

    bool SetTrackNodePosition(uint nodeIndex, const CVector& position);
    bool GetTrackNodePosition(uint nodeIndex, CVector& position);

    inline const std::vector<STrackNode>& GetNodes() const { return m_Nodes; }
    inline std::size_t                    GetNumberOfNodes() const { return m_Nodes.size(); }

    inline void SetLastNodesLinked(bool link) { m_LinkLastNodes = link; }
    inline bool GetLastNodesLinked() { return m_LinkLastNodes; }

    inline bool  IsDefault() { return m_DefaultTrackId != 0xFF; }
    inline uchar GetDefaultTrackId() { return m_DefaultTrackId; }

    virtual void Unlink() override {}
    bool         ReadSpecialData(const int iLine) override { return false; }

private:
    CTrainTrackManager* m_pManager;

    std::vector<STrackNode> m_Nodes;
    bool                    m_LinkLastNodes;
    bool                    m_Default;
    uchar                   m_DefaultTrackId;
};
